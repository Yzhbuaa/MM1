//
// Created by Zihao on 2020/3/9.
//

#include "Server.h"

// Currently, the implementation is the same with the InterarrivalTimeCalc() method in Customer class.
double Server::get_service_time_(const std::mt19937::result_type sd, const double lambda) {
    std::mt19937 rng; // sets pseudo-random engine
    rng.seed(sd); // sets random seed
    std::uniform_real_distribution<double> dist_zero2one(0,1); // distribution in range [0,1)
    service_time_ =(-lambda)*log(dist_zero2one(rng));
    return service_time_;

}
void Server::set_total_customer_waiting_time_(Customer *customer_going_to_departure) {
    total_customer_waiting_time_ += customer_going_to_departure->get_leaving_time_() - customer_going_to_departure->get_appear_time_();
}
