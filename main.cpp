
// General
#include <cstdio>
#include <cmath>
#include <ctime>
#include <functional>
#include <thread>

// STL
#include <vector>

// Streams
#include <iomanip>
#include <iostream>

// Local
#include "queue.hpp"
#include "utility.hpp"

/*
 * NOTE
 *
 * All times are given in SECONDS and represented by a `double`.
 */

unsigned int minutes { 0 };

std::mutex mtx;

void serve(QueueEnvironment& env)
{
/*
 * Serve customers in the queue.
 */
    for (;;) {
        mtx.lock();
        if (minutes == time_limit) { mtx.unlock(); break; }
        mtx.unlock();
        if (env.q.serve()) {
//            mtx.lock();
//            std::cout
//                << "(" << env.q.size() << ") "
//                << "Customer served in queue " << env.q.num() << "."
//                << std::endl;
//            mtx.unlock();
        }
    }
    std::cout << "Exiting serve." << std::endl;
}

void arrive(QueueEnvironment& env)
/*
 * Let customers arrive to the queue. The arrival is modeled after a Poisson
 * process.
 */
{
    for (;;) {
        mtx.lock();
        if (minutes == time_limit) { mtx.unlock(); break; }
        mtx.unlock();
        sleep(60.0 * invpoiss(env.dist.lambda));
        mtx.lock();
        Customer c { gauss(env.dist.mu, env.dist.sigma) };
        env.q.arrive(c);
        unsigned int wt = round(env.q.wait_time());
        if (wt < env.hist.size()) {
            ++env.hist[wt];
        }
//        std::cout
//            << "(" << env.q.size() << ") "
//            << "Customer arrived to queue " << env.q.num() << ". "
//            << "Wait time: " << std::setw(5) << env.q.wait_time() << " seconds."
//            << " Number of items: " << std::setw(5) << c.num_items() << "."
//            << std::endl;
        mtx.unlock();
    }
    std::cout << "Exiting arrive." << std::endl;
}

#if 0
void print(const Queue& q)
/*
 * Print a queue on one line, reversing it with \r each iteraton.
 *
 * TODO:
 *  Come up with some better way of printing things, since the below just
 *  overwrites whatever else is printed to std::cout.
 *
 * @arg q       A queue of customers
 */
{
    for (;;) {
        std::cout << "\r" << q.to_string();
    }
}
#endif

void timer_minutes()
{
    mtx.lock();
    std::cout << "Timer started." << std::endl;
    minutes = 1;
    mtx.unlock();
    for (;;) {
        sleep(60);
        mtx.lock();
        std::cout << minutes << " minutes passed." << std::endl;
        if (minutes == time_limit) { mtx.unlock(); break; }
        else { ++minutes; }
        mtx.unlock();
    }
    std::cout << "Exiting timer_minutes." << std::endl;
}

void run_queue(QueueEnvironment& env)
{
    // Thread for serving customers
    std::thread thread_serve { serve, std::ref(env) };

    // Thread for customers arriving
    std::thread thread_arrive(arrive, std::ref(env));

    // Thread for printing the queue to the terminal
//  std::thread thread_print(print, std::ref(q));

    // Join threads; however, they run indefinitely so this won't really happen.
    thread_serve  .join();
    thread_arrive .join();
//  thread_print  .join();
}

void print_histogram(const QueueEnvironment& env)
{
    mtx.lock();
    std::cout << std::string(80, '-') << std::endl;
    std::cout << "Histogram of queue " << env.q.num() << ":\n" << std::endl;
    for (size_t i = 0; i < env.hist.size(); ++i) {
        std::cout
            << i << ": " << ((i < 100) ? " " : "") << ((i < 10) ? " " : "")
            << std::string(env.hist[i] / 50, '*')
            << std::endl;
    }
    std::cout << std::string(80, '-') << "\n\n" << std::endl;
    mtx.unlock();
}

template <typename T>
T read_value(std::function<bool(T)> pred, const std::string& msg)
{
    T value;
    bool retry;
    do {
        std::cin >> value;
        retry = !pred(value) || std::cin.fail();
        if (retry) {
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cout << msg << std::endl;
        }
    } while (retry);
    return value;
}

int main()
{
    std::cout << "\n  ~~~~ Queueing simulation ~~~~\n" << std::endl;

    auto is_positive = [](size_t n){ return n >= 1; };

    std::cout << "How many queues?" << std::endl;
    auto num_queues = read_value<size_t>(is_positive,
                                         "Invalid number of queues.");

    std::cout << "How large histogram?" << std::endl;
    auto hist_size  = read_value<size_t>(is_positive,
                                         "Invalid histogram size.");

    // Set seed for the rand() function used to generate distributions
    srand(time(0));

    // ...
    std::vector<QueueEnvironment> envs;
    envs.reserve(num_queues);

    // Thread for keeping track of how many minutes has passed
    std::thread thread_timer(timer_minutes);

    // Initialize and add all threads to a vector
    std::vector<std::thread> threads;
    for (size_t i = 0; i < num_queues; ++i) {
        envs.push_back(QueueEnvironment { i + 1 });
        envs[i].hist        = std::vector<unsigned int>(hist_size);
        // TODO: Set different variables...
        envs[i].dist.lambda = 4.0;  // λ - for Poisson
        envs[i].dist.mu     = 10.0; // μ - for Gaussian
        envs[i].dist.sigma  = 6.0;  // σ - for Gaussian
        threads.push_back(std::thread(run_queue, std::ref(envs[i])));
    }

    for (auto& t : threads) {
        t.join();
    }
    thread_timer.join();

    std::cout << "size = " << envs.size() << std::endl;

    // Show the result(s)
    for (const auto& env : envs) {
        print_histogram(env);
    }
}

