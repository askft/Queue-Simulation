
#include <deque>

#include "customer.hpp"
#include "utility.hpp"

#ifndef QUEUE
#define QUEUE

class Queue {

public:
    Queue(unsigned int num) : num_{num} { }

    unsigned int num() const { return num_; }

    const Customer& front() const { return self_.front(); }

    bool empty() const { return self_.empty(); }

    size_t size() const { return self_.size(); }

    // Customer arrives to queue
    void arrive(Customer c) { self_.push_back(std::move(c)); }

    // Serve the customer first in the queue
    // return true if a customer was served
    bool serve()
    {
        if (!self_.empty()) {
            sleep(self_.front().service_time()); // Serve customer's items
            self_.pop_front();                   // Customer done
            return true;
        } else {
            return false;
        }
    }

    double total_wait_time() const
    {
        double t {0};
        for (const Customer& c : self_) {
            t += c.service_time();
        }
        return t;
    }

    std::string to_string() const
    {
        std::string s {""};
        for (unsigned long i = 0; i < self_.size(); ++i) { s += "<"; }
        return s;
    }

    std::deque<Customer> queue() { return self_; }

private:
    std::deque<Customer> self_;
    unsigned int num_;
};

#endif

