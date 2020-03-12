//
// Created by Zihao on 2020/3/6.
//

#ifndef MM1_PROJ_EVENTSCHEDULER_H
#define MM1_PROJ_EVENTSCHEDULER_H

#include "Server.h"
#include "Customer.h"
#include <iostream>
#include <random>
#include <list>
#include <vector>
#include <set>

class Customer;
class Server;
struct Input{

    Input():server_number(0), mean_interarrival_time(0), mean_service_time(0),
            maximum_number_of_customer(0),maximum_queue_length(0){}

//    Input(std::istream &is){ read(is,*this);}
//
//    std::istream &read(std::istream &is, Input &input){
//        is >> input.server_number >> input.mean_interarrival_time >>input.mean_service_time>>input.maximum_number_of_customer >> input.maximum_queue_length;
//        return is;
//    }
// TODO::make the member variables const.
    int server_number;
    double mean_interarrival_time;
    double mean_service_time;
    int maximum_number_of_customer;
    int maximum_queue_length;
};

class EventScheduler {
    // uses the default constructor and destructor.

public:

    // initializer
    void Initialize(const Input &i);

    // process
    void Process();

    // decides which event should happen next, set the corresponding server.
    void set_event_customer_(){
        event_customer_ = *(future_event_set_.begin());
    }
    // TODO:: MMN modified
    void set_event_server_(){
        event_server_ = event_customer_->get_server_();
    }

    // set time_last_event_
    // set current_time_
    // set time_since_last_event_
    void AdvanceClock(){
        set_time_last_event_();
        set_current_time_(event_customer_->get_event_time_());
        set_time_since_last_event_();
    }

    // triggers arrive event.
    void Arrive();

    // triggers departure event.
    void Departure();

    // setters
    void set_current_time_(double time){ current_time_ = time;}
    double set_time_last_event_(){ time_last_event_ = current_time_; return time_last_event_;}
    double set_time_since_last_event_(){ time_since_last_event_ = current_time_ - time_last_event_;}

    // getters
    double get_current_time_() const{return current_time_;}
    double get_time_last_event_() const {return time_last_event_;}
    double get_time_since_last_event() const{return time_since_last_event_;}

    // puts an event in order of occurrence
    // test code:
    //    std::vector<Customer> customer_vec_;
    //    for (int i = 0; i < 10; ++i) {
    //        Customer customer(server_,event_scheduler.get_current_time_()+i, input.mean_interarrival_time);
    //        cout << customer.get_interarrival_time_() << " " ;
    //        customer_vec_.push_back(customer);
    //    }
    //    cout << endl;
    //
    //    for(auto itr=customer_vec_.begin();itr!=customer_vec_.end();++itr)
    //        event_scheduler.EventInFutureEventSet(&(*itr));
    //    event_scheduler.PrintFutureEventSet();
    void EventInFutureEventSet(Customer *customer){
        customer->set_event_time_();
        future_event_set_.insert(customer);
    }

    // takes out an event which should happen now, and put it into the current_event_list
    void EventOutFutureEventSet(){future_event_set_.erase(future_event_set_.begin());}

    void CustomerInVector(Customer customer){
        customer_vec_.push_back(customer);
    }

    void CalculateStatistics();

    // print out the future_event_set_
    void PrintFutureEventSet(){
        for(auto itr = future_event_set_.cbegin(); itr!=future_event_set_.cend();++itr){
            std::cout << (*itr)->get_event_time_() << " ";//(((*itr)->get_leaving_time_()!=Infinity)?((*itr)->get_leaving_time_()):((*itr)->get_appear_time_())) << " ";
        }
        std::cout << std::endl;
    }

    void PrintOutStatistics(){
        //TODO:: MMN modified
        event_server_->SetStatistics(current_time_);
        event_server_->PrintOutStatistics();
        std::cout<<std::endl;
        std::cout<< "Simulation stop at " << current_time_ <<"s"<<std::endl;
    }

private:
    // time
    double current_time_{0.0}; // current simulation time.
    double time_last_event_{0.0}; // time when last event triggers in corresponding server(currently there is only one event_server_).
    double time_since_last_event_{0.0}; // current_time_ - time_last_event_(in corresponding server).

    Server *event_server_{nullptr}; // server which is/are in used, treated as a statistical "big container"  default constructed
    Customer *event_customer_{nullptr}; // currently processing customer, treat as event element, default constructed

    std::vector<Customer> customer_vec_; // stores all customers
    std::vector<Server>   server_vec_; //stores all servers

    // future event list and current event list.
    std::set<Customer*,PCompare> future_event_set_;
    std::set<Customer*,PCompare> current_event_set_;

    // input
    Input input;
};


#endif //MM1_PROJ_EVENTSCHEDULER_H
