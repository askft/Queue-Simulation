//    using clk   = std::chrono::steady_clock;
//    using sec   = std::chrono::seconds;
//    using msec  = std::chrono::milliseconds;
//
//    unsigned int    mins    { 0 };
//    auto            start   = clk::now();
//    for (;;) {
//        auto now    = clk::now();
//        auto sdiff  = std::chrono::duration_cast<sec>( now - start).count();
//        auto msdiff = std::chrono::duration_cast<msec>(now - start).count();
//
//        if (msdiff == 1000) {
////            start = clk::now();
//            std::cout << sdiff << " seconds passed" << std::endl;
//        }
//        if ((sdiff + 1) % 60 == 0) {
////            start = clk::now();
//            std::cout << sdiff << std::endl;
//            std::cout << ++mins << " minutes passed" << std::endl;
//        }
//
//
////        if (std::chrono::duration_cast<msec>(now - start).count()
////                % static_cast<int>(time_speedup * 60) == 0) {
////            std::cout << ++mins << " minutes passed" << std::endl;
////        }
//    }




//    using clk   = std::chrono::steady_clock;
//    using ms    = std::chrono::milliseconds;
//    auto start = clk::now();
//    PoissonDistribution poiss   { 3 };
//    int mins = 0;
//    for (;;) {
//        auto now = clk::now();
//        if (std::chrono::duration_cast<ms>(now - start).count()
//                % static_cast<int>(speedup * (60 * 1000)) == 0) {
//            std::cout << ++mins << " minutes passed" << std::endl;
//        }
//        std::cout << poiss() << std::endl;
////        sleep( HOW LONG ? );
//    }


//    // Create a random queue
//    for (;;) {
//        q.run
//    }
//    q.push_back(
//
//    std::vector<double> wait_times;
//
//    std::vector<int> histogram(100);
//
//    for (int i = 0; i < 10000; ++i) {
//        auto wait_time = 
//        ++histogram[wait_time];
//    }



//    std::vector<Time> arrival_times;
//    for (int i = 0; i < 1000) {
//        // maybe queue is better
//        auto random_arrival_time = poiss(gen);
//        arrival_times.push_back(
//    }
//    for (;;) {
//        
//    }


#if 0
void arrive(Queue& q,
            InversePoissonDistribution& inv_poiss,
            NormalDistribution& norm)
{
    mtx.lock();
    std::cout << "    arrive" << std::endl;
    mtx.unlock();
    for (;;) {
//        sleep(60.0 * inv_poiss());
        sleep(60.0 * invpoiss(4.0));
        q.arrive(Customer{norm()});
        mtx.lock();
        std::cout << "(" << q.size() << ") Customer arrived." << std::endl;
        mtx.unlock();
    }
}
#endif

