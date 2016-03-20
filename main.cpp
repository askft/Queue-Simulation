
// General
#include <cstdio>
#include <ctime>
#include <functional>
#include <thread>

// STL
#include <vector>

// Streams
#include <iostream>

// Local
#include "customer.hpp"
#include "queue.hpp"
#include "utility.hpp"

/*
 * NOTE
 *
 * All times are given in SECONDS and represented by a `double`.
 */

std::mutex mtx;

void serve(Queue& q)
{
/*
 * Serve customers in the queue.
 *
 * @arg q   A queue of customers
 *
 */
    for (;;) {
        if (q.serve()) {
            mtx.lock();
            std::cout
                << "(" << q.size() << ") Customer served in queue " << q.num()
                << "." << std::endl;
            mtx.unlock();
        }
    }
}

void arrive(Queue& q, const double lambda, const double mu, const double sigma)
/*
 * Let customers arrive to the queue. The arrival is modeled after a Poisson
 * process.
 *
 * @arg q       A queue of customers
 * @arg lambda  Argument to invpoiss
 * @arg mu      Argument to gauss (mean)
 * @arg sigma   Argument to gauss (standard deviation)
 */
{
    for (;;) {
        sleep(60.0 * invpoiss(lambda));
        q.arrive(Customer(gauss(mu, sigma)));
        mtx.lock();
        std::cout
            << "(" << q.size() << ") Customer arrived to queue " << q.num()
            << "." << std::endl;
        mtx.unlock();
    }
}

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

void timer_minutes()
{
    std::cout << "Timer started." << std::endl;
    for (auto minutes = 1; true; ++minutes) {
        sleep(60);
        std::cout << minutes << " minutes passed." << std::endl;
    }
}

void run_queue(unsigned int num)
{
    const double lambda { 2.0 };    // λ
    const double mu     { 10.0 };   // μ
    const double sigma  { 4.0 };    // σ

    Queue q { num };

    // Thread for serving customers
    std::thread thread_serve {serve, std::ref(q)};

    // Thread for customers arriving
    std::thread thread_arrive(arrive, std::ref(q), lambda, mu, sigma);

    // Thread for printing the queue to the terminal
//    std::thread thread_print(print, std::ref(q));

    // Join threads; however, they run indefinitely so this won't really happen.
    thread_serve  .join();
    thread_arrive .join();
//    thread_print  .join();
}

void test_hist();
void test_poiss();

int main()
{
    std::cout << "\n  ~~~~ Queueing simulation ~~~~\n" << std::endl;

    std::cout << "How many queues?" << std::endl;

    unsigned long num_queues;
    bool retry;
    do {
        std::cin >> num_queues;
        retry = num_queues < 1 || std::cin.fail();
        if (retry) {
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cout << "Invalid number of queues." << std::endl;
        }
    } while (retry);

    auto t = time(0);
    srand(t);
    std::cout << "srand initialized to " << t << "." << std::endl;


//    test_hist();
//    test_poiss();

    // Thread for keeping track of how many minutes has passed
    std::thread thread_timer(timer_minutes);

    std::vector<std::thread> threads;

    for (unsigned long i = 0; i < num_queues; ++i) {
        threads.push_back(std::thread(run_queue, i + 1));
    }

    thread_timer.join();

    for (unsigned long i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }
}

void test_hist()
{
    std::vector<int> hist (45 + 1);

    int nrolls = 100000;

    for (int i = 0; i < nrolls; ++i) {
        unsigned int x = 60 * invpoiss(4.0);
        if (x < hist.size()) {
            ++hist[x];
        }
    }

    for (size_t i = 0; i < hist.size(); ++i) {
        std::cout
            << i << ": " << ((i < 10) ? " " : "")
            << std::string(hist[i] / 500, '*')
            << std::endl;
    }
}

void test_poiss()
{
//    std::cout << "Break test with 'x'." << std::endl;
    for (int i = 0; i < 50; ++i) {
        std::cout << 60 * invpoiss(4.0) << std::endl;
//        if (getchar() == 'x') {
//            break;
//        }
    }
}

