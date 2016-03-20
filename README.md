# Queue Simulation

Multithreaded real-time queue simulation in C++.

Requires C++11.

## About

The program performs a real-time simulation of customers arriving at a queue (a
line). The time between each customer's arrival is Poisson distributed, and the
`lambda` parameter can be set inside the program.

Each customer is given a number of items to be handled at the head of the queue.
(Think grocery shopping). The number of items are Gaussian (normal) distributed,
and the `mu` and `sigma` parameters can be set inside the program.

Inside `utility.hpp`, a few useful constants can be found, such as for speeding
up the simulations and modifying how long time it takes to serve an item.

