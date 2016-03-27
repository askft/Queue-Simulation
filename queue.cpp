
#include <string>

#include "queue.hpp"
#include "utility.hpp"

void
Queue::arrive(const Customer& c)
{
    self_.push_back(c);
}

bool
Queue::serve()
{
    if (!self_.empty()) {
        sleep(self_.front().service_time()); // Serve customer's items
        self_.pop_front();                   // Customer done
        return true;
    } else {
        return false;
    }
}

double
Queue::wait_time() const
{
    double t {0};
//    for (unsigned int i = 0; i < self_.size() - 1; ++i) { // NOTE size - 1
//        t += self_[i].service_time();
    for (const Customer& c : self_) {
        t += c.service_time();
    }
    return t;
}

std::string
Queue::to_string() const
{
    std::string s {""};
    for (unsigned long i = 0; i < self_.size(); ++i) {
        s += "<";
    }
    return s;
}

