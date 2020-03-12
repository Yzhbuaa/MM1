//
// Created by Zihao on 2020/3/6.
//

#include "EventScheduler.h"

void EventScheduler::CalculateStatistics() {
    event_server_->set_queue_area_(time_since_last_event_);
    event_server_->set_server_status_area(time_since_last_event_);
}

void EventScheduler::Initialize(const Input &i){
    input = i ; //get the input
    Server server; //initializes server
    Customer first_customer(&server,current_time_,input.mean_service_time); // generate the first customer
    customer_vec_.push_back(first_customer); // records customer
    event_customer_ = &(customer_vec_.back());
    set_event_server_();
    event_customer_->set_appear_time_(current_time_);

    EventInFutureEventSet(event_customer_); // add the first customer into future event list
}

void EventScheduler::Arrive() {
    // schedule next arrive event
    // TODO::select server
    Customer new_customer(event_server_,current_time_,input.mean_interarrival_time);
    new_customer.set_appear_time_(current_time_);
    customer_vec_.push_back(new_customer);
    EventInFutureEventSet(&(customer_vec_.back()));

    if(event_server_->get_server_status_()==ServerStatus::IDLE){
        event_server_->set_server_status_(ServerStatus::BUSY);

        event_server_->IncreaseTotalCustomerServedNumber();

        // schedule a departure event
        double service_time = event_server_->get_service_time_(current_time_,input.mean_service_time);
        event_customer_->set_leaving_time_(current_time_+service_time);
        EventInFutureEventSet(event_customer_);
    }
    else{// BUSY
        if(event_server_->get_queue_length_()<input.maximum_queue_length){
            event_server_->CustomerInQueue(event_customer_);
        }
        else{
            std::cout<< "queue length too long, stop simulation.";
        }
    }
}

void EventScheduler::Departure() {

}

void EventScheduler::Process() {
    //TODO:: MMN modified choose server
    while(event_server_->get_total_customer_served_number_()<input.maximum_number_of_customer){
        set_event_customer_();
        AdvanceClock();
        CalculateStatistics();

        // if the event_customer_ hasn't been served yet.
        if(event_customer_->get_leaving_time_()==Infinity){
            Arrive();
        }
        else{
            Departure();
        }
    }
}



