
#include <chrono>
#include <thread>

#include <cmath>
#include <cstdlib>
#include <limits>

#include "utility.hpp"

const double    time_speedup    { 1.0 / (60.0 * 100000.0) };
const double    time_serve_item { 2.0 };
const double    time_limit      { 100000.0 };

void sleep(double s)
{
    s *= time_speedup;
    unsigned long long ms = static_cast<unsigned long>(s * 1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

double invpoiss(double lambda)
{
    double u {static_cast<double>(rand()) / RAND_MAX}; // [0.0, 1.0)
    return -log(1.0 - u) / lambda; // 1.0 - r gives (0.0, 1.0]
}

double gauss(double mu, double sigma)
{
    const double pi { 3.14159265358979323846 };
    double u        { static_cast<double>(rand()) / RAND_MAX }; // [0.0, 1.0)
    double theta    { 2 * pi * u };
    double r        { sqrt(-2.0 * log(1.0 - u)) };
    double x        { r * cos(theta) };
//  double y        { r * sin(theta) };
    return x * sigma + mu;
//  return std::make_pair(x * sigma + mu, y * sigma + mu);
}

