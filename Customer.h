//
// Created by Zihao on 2020/3/6.
//

#ifndef MM1_PROJ_CUSTOMER_H
#define MM1_PROJ_CUSTOMER_H

#include <random>
#include "Server.h"

class Server;
class Customer {
public:

    // constructor
//    Customer():interarrival_time_(0.0),appear_time_(0.0),
//    leaving_time_(0.0),waiting_in_queue_time_(0.0),server_(NULL){}

    Customer(const Server &s):interarrival_time_(0.0),appear_time_(0.0),
                        leaving_time_(1.0e30),waiting_in_queue_time_(0.0),server_(s){
    }

    Customer(const Server &s, const std::mt19937::result_type sd, const double lambda):Customer(s){
        InterarrivalTimeCalc(sd,lambda);
    }

    // Returns the interarrival time of this Customer using exponential distribution
    //
    // input:
    //      lambda, arrival rate(people/second) or serving rate(people/second).
    //      random seed sd
    //
    // output:
    //      the interarrival time of this Customer
    //
    // Example(client code):
    //      Customer customer1;
    //      int cnt = 0;
    //      double lambda = 1/3600;
    //      for(int i=0;i<1000;++i){
    //          long double x = customer1.InterarrivalTimeCalc(i,lambda);
    //          std::cout << x << std::endl;
    //          cnt+=x;
    //      }
    //      std::cout<< cnt/1000 <<std::endl; // approximately 3600
    double InterarrivalTimeCalc(const std::mt19937::result_type sd, const double lambda);

    double set_appear_time_(double current_time){ appear_time_ = current_time + interarrival_time_; return appear_time_;}
    double get_appear_time_() const {return appear_time_;}

    double get_interarrival_time_() const{ return interarrival_time_;}
    double get_waiting_in_queue_time_() const{return waiting_in_queue_time_;}

    double get_leaving_time_() const { return  leaving_time_;}
    double set_leaving_time_(double time) {leaving_time_=time;}


    const Server &get_server() const {return server_;};

    bool Arrive();

    // Departure event
    bool Departure();

private:
    double interarrival_time_; // time interval between last customer's arrival time and this customer's arrival time.
    double appear_time_; // this customer's appear_time_ = current_time_ + interarrival_time_.
    double leaving_time_; // this customer's leaving_time_
    double event_time_; // event_time = appear_time_ or event_time_ = leaving_time_ depending on the
    double waiting_in_queue_time_; // waiting_in_queue_time_ = leaving_time_ - appear_time_.

    const Server &server_; // server that servers this customer.
};

// Customer comparator
struct PCompare{
    inline bool operator()(const Customer *lhs, const Customer *rhs) const{
        double lhs_event_time = (lhs->get_leaving_time_())?(lhs->get_leaving_time_()):(lhs->get_appear_time_());
        double rhs_event_time = (rhs->get_leaving_time_())?(rhs->get_leaving_time_()):(rhs->get_appear_time_());
        return (lhs_event_time < rhs_event_time);
    }
};

#endif //MM1_PROJ_CUSTOMER_H
