
#ifndef UTILITY
#define UTILITY

#include <vector>

#include "queue.hpp"

extern const double time_speedup;
extern const double time_serve_item;
extern const double time_limit;

struct QueueEnvironment {
    QueueEnvironment(size_t num) : q(num) { }
    Queue q;
    std::vector<unsigned int> hist;
    struct {
        double lambda;
        double mu;
        double sigma;
    } dist;
};

void    sleep       (double s);
double  invpoiss    (double lambda);
double  gauss       (double mu, double sigma);

#endif

