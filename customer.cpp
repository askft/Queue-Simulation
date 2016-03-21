
#include "customer.hpp"
#include "utility.hpp"

double
Customer::service_time() const
{
    return num_items_ * time_serve_item; // TODO Add other values to this
}

