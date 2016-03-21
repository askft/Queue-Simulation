
#ifndef CUSTOMER
#define CUSTOMER

class Customer {
public:
    Customer(double num_items) : num_items_{num_items} { }

    // Get number of items this customer holds
    double num_items() const { return num_items_; }
    
    // Calculate the time it takes to serve this customer
    double service_time() const;

private:
    double num_items_;
};

#endif

