
#include "utility.hpp"

#ifndef CUSTOMER
#define CUSTOMER

class Customer {
public:
    Customer(double num_items) : num_items_{num_items} { }

    double service_time() const
    {
        return num_items_ * time_item;
    }

private:
    double num_items_;
};

#endif

