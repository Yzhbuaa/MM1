//
// Created by Zihao on 2020/3/6.
//

#include "Customer.h"
#include <cmath>


// uses mt19937 as a pseudo-random generator and uniform_real_distribution<double>
// to generate the interarrival time of this Customer
//
// why don't use rand() and srand()?
// modulo will introduce bias into the random numbers
// e.g. if a\in[0,10]\and N, then a%3\in{0,1,2,3},
// apparently the remainders of a%3 have more 0 and 1 than 2.
// And modulo uses division which costs hundreds of clock cycles.
double Customer::InterarrivalTimeCalc(const std::mt19937::result_type sd, const double lambda) {
    std::mt19937 rng; // sets pseudo-random engine
    rng.seed(sd); // sets random seed
    std::uniform_real_distribution<double> dist_zero2one(0,1); // distribution in range [0,1)
    interarrival_time_ =-(lambda)*log(dist_zero2one(rng));

    return interarrival_time_;
}

