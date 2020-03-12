//
// Created by Zihao on 2020/3/6.
//

#ifndef MM1_PROJ_CUSTOMER_H
#define MM1_PROJ_CUSTOMER_H

#include <random>
#include "Server.h"


const double Infinity = -1;

class Server;
class Customer {
public:

    // constructor
    explicit Customer(Server *s):interarrival_time_(0.0),appear_time_(0.0),
                        leaving_time_(Infinity),waiting_in_queue_time_(0.0),server_(s),event_time_{0.0}{
    }

    Customer(Server *s, const std::mt19937::result_type sd, const double lambda):Customer(s){
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
    double set_leaving_time_(double current_time,double service_time) {leaving_time_=current_time+service_time;}

    double set_event_time_(){event_time_ = (leaving_time_<0)?(appear_time_):(leaving_time_);}
    double get_event_time_() const{return event_time_;}

    Server *get_server_() const {return server_;}
    void   *set_server_(Server *server) {server_ = server;}

    bool Arrive();

    // Departure event
    bool Departure();

private:
    double interarrival_time_{0.0}; // time interval between last customer's arrival time and this customer's arrival time.
    double appear_time_{0.0}; // this customer's appear_time_ = current_time_ + interarrival_time_.
    double leaving_time_{0.0}; // this customer's leaving_time_
    double event_time_{0.0}; // event_time = appear_time_ or event_time_ = leaving_time_ depending on whether this customer has been served.
    double waiting_in_queue_time_{0.0}; // waiting_in_queue_time_ = leaving_time_ - appear_time_.

    Server *server_{nullptr}; // server_ that servers this customer.
};

// Customer comparator
struct PCompare{
    inline bool operator()(const Customer *lhs, const Customer *rhs) const{
        double lhs_event_time = lhs->get_event_time_();//(lhs->get_leaving_time_()!=Infinity)?(lhs->get_leaving_time_()):(lhs->get_appear_time_());
        double rhs_event_time = rhs->get_event_time_();//(rhs->get_leaving_time_()!=Infinity)?(rhs->get_leaving_time_()):(rhs->get_appear_time_());
        return (lhs_event_time < rhs_event_time);
    }
};

#endif //MM1_PROJ_CUSTOMER_H
