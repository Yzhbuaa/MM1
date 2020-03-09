//
// Created by Zihao on 2020/3/9.
//

#include "Server.h"

// Currently, the implementation is the same with the InterarrivalTimeCalc() method in Customer class.
double Server::ServiceTimeCalc(const std::mt19937::result_type sd, const double lambda) {
    std::mt19937 rng; // sets pseudo-random engine
    rng.seed(sd); // sets random seed
    std::uniform_real_distribution<double> dist_zero2one(0,1); // distribution in range [0,1)

    return (-1/lambda)*log(dist_zero2one(rng));
}