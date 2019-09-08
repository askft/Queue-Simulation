
#include <cmath>
#include <ctime>
#include <random>

#ifndef POISSON_DISTRIBUTION
#define POISSON_DISTRIBUTION
class PoissonDistribution {
public:
    PoissonDistribution(double lambda) : poiss{lambda} { }
    int operator()() { return poiss(gen); }
private:
    std::default_random_engine      gen;
    std::poisson_distribution<int>  poiss;
};
#endif

#ifndef INVERSE_POISSON_DISTRIBUTION
#define INVERSE_POISSON_DISTRIBUTION
class InversePoissonDistribution {
public:
    InversePoissonDistribution(double lambda) : lambda{lambda} { }
    int operator()()
    {
        double r = {static_cast<double>(rand()) / RAND_MAX}; // [0.0, 1.0)
        return -log(1.0 - r) / lambda; // 1.0 - r gives (0.0, 1.0]
    }
private:
    double lambda;
};
#endif

#ifndef NORMAL_DISTRIBUTION
#define NORMAL_DISTRIBUTION
class NormalDistribution {
public:
    NormalDistribution(double mean, double dev)
        : norm{mean, dev} { }
    double operator()() { return norm(gen); }
private:
    std::default_random_engine          gen;
    std::normal_distribution<double>    norm;
};
#endif

#ifndef UNIFORM_REAL_DISTRIBUTION
#define UNIFORM_REAL_DISTRIBUTION
class UniformRealDistribution {
public:
    UniformRealDistribution() : uniform{0, 1} { }
    int operator()() { return uniform(gen); }
private:
    std::default_random_engine              gen;
    std::uniform_real_distribution<double>  uniform;
};
#endif

