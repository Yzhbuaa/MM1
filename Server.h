//
// Created by Zihao on 2020/3/9.
//

#ifndef QUEUE_MM1_SERVER_H
#define QUEUE_MM1_SERVER_H

#include <random>
#include <queue>
#include "Customer.h"

// TODO:: put the global variate to somewhere else?
enum ServerStatus{
    IDLE,
    BUSY
};

class Customer;

class Server {

public:
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
    //      Server server1;
    //      int cnt = 0;
    //      double lambda = 1/3600;
    //      for(int i=0;i<1000;++i){
    //          long double x = server1.get_service_time_(i,lambda);
    //          std::cout << x << std::endl;
    //          cnt+=x;
    //      }
    //      std::cout<< cnt/1000 <<std::endl; // approximately 3600
    double get_service_time_(const std::mt19937::result_type sd, const double lambda);

    // example:
//    Server server1;
//    server1.set_server_status_(ServerStatus::BUSY);
//    cout << "the event_server_ status is:" << server1.get_server_status_() << endl;
    ServerStatus get_server_status_() const {return server_status_;}

    ServerStatus set_server_status_(ServerStatus ss){ server_status_ = ss; return server_status_;}

    const int get_queue_length_() const {return customer_queue_.size();}

    void CustomerInQueue(Customer *customer){customer_queue_.push(customer);}
    void CustomerOutQueue(){customer_queue_.pop();}
    Customer *CustomerNextBeingServed(){return customer_queue_.front();}

    int get_total_customer_served_number_() const {return total_customer_served_number_;}

    void IncreaseTotalCustomerServedNumber(){++total_customer_served_number_;}

    void set_queue_area_(double time_since_last_event){queue_area_ += customer_queue_.size()*time_since_last_event;}

    void set_server_status_area(double time_since_last_event){server_status_area += server_status_*time_since_last_event;}

private:
    double service_time_{0.0};

    std::queue<Customer*> customer_queue_; // TODO::how would this variate be destructed?

    // statistic(each server has its own statistic, currently there is only one event_server_ in use)
    // server utilization
    ServerStatus server_status_{ServerStatus::IDLE};
    double server_status_area{0.0};
    double server_utilization_{0.0}; // server_status_ * time_since_last_event

    // average customer waiting time in queue
    int total_customer_served_number_{0};
    double total_customer_waiting_time_in_queue_{0.0};
    double average_customer_waiting_time_in_queue_{0.0};

    // average customer number in queue
    double queue_area_{0.0}; // queue_area_ += customer_queue_.size() * time_since_last_event_
    double average_customer_number_in_queue_{0.0}; // queue_area_ / current_time_
};


#endif //QUEUE_MM1_SERVER_H
