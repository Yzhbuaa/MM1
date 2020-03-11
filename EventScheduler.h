//
// Created by Zihao on 2020/3/6.
//

#ifndef MM1_PROJ_EVENTSCHEDULER_H
#define MM1_PROJ_EVENTSCHEDULER_H

#include "Server.h"
#include "Customer.h"
#include <random>
#include <list>
#include <vector>
#include <set>

class EventScheduler {
    // uses the default constructor and destructor.

public:

    // decides which event should happen next.
    Customer* select_event();

    // setters
    void set_current_time_(double time){ current_time_ = time;}
    double set_time_last_event_(){ time_last_event_ = current_time_; return time_last_event_;}
    double set_time_since_last_event_(){ time_since_last_event_ = current_time_ - time_since_last_event_;}

    // getters
    double get_current_time_() const{return current_time_;}
    double get_time_last_event_() const {return time_last_event_;}
    double get_time_since_last_event() const{return time_since_last_event_;}

    // puts an event in order of occurrence
    // TODO::IMPL
    void EventInFutureEventSet(Customer *customer){future_event_set_.emplace(customer);}

    // takes out an event which should happen now, and put it into the current_event_list
    // TODO::IMPL
    void EventOutFutureEventSet(){}

private:
    // time
    double current_time_{0.0}; // current simulation time.
    double time_last_event_{0.0}; // time when last event triggers in corresponding server(currently there is only one server).
    double time_since_last_event_{0.0}; // current_time_ - time_last_event_(in corresponding server).

    // future event list and current event list.
    std::set<Customer*,PCompare> future_event_set_;
    std::set<Customer*,PCompare> current_event_set_;
};


#endif //MM1_PROJ_EVENTSCHEDULER_H
