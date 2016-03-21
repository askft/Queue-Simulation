
#ifndef QUEUE
#define QUEUE

#include <deque>

#include "customer.hpp"

class Queue {

public:
    Queue(size_t num) : num_{num} { }

    // Accessor functions
    size_t                  num()   const { return num_; }
    std::deque<Customer>    queue() const { return self_; }
    const Customer&         front() const { return self_.front(); }
    bool                    empty() const { return self_.empty(); }
    size_t                  size()  const { return self_.size(); }

    // Customer arrives to queue (add customer last in queue)
    void arrive(const Customer& c);

    // Serve the customer first in the queue, true if a customer was served
    bool serve();

    // Calculate total wait time (how long it takes to serve the entire queue)
    double wait_time() const;

    // Return a string representation of the queue
    std::string to_string() const;

private:
    size_t                  num_;
    std::deque<Customer>    self_;
};

#endif

