//
// Created by Zihao on 2020/3/6.
//

#include "EventScheduler.h"

void EventScheduler::CalculateStatistics() {
    event_server_->set_queue_area_(time_since_last_event_);
    event_server_->set_server_status_area(time_since_last_event_);
}

void EventScheduler::Initialize(const Input &i){
    customer_vec_.reserve(i.maximum_number_of_customer);
    input = i ; //get the input
    Server server; // initialize server
    server_vec_.push_back(server);
    Customer first_customer(&(server_vec_.front()),current_time_,input.mean_service_time); // generate the first customer
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
    new_customer.set_server_(&(server_vec_.front())); //TODO::MMN modified
    customer_vec_.push_back(new_customer);
    EventInFutureEventSet(&(customer_vec_.back()));

    if(event_server_->get_server_status_()==ServerStatus::IDLE){
        event_server_->set_server_status_(ServerStatus::BUSY);

        event_server_->CustomerInQueue(event_customer_);
        event_server_->IncreaseTotalCustomerServedNumber();// everyone who successfully arrives should be counting in the total customer served number

        // schedule a departure event, current+1 to avoid that the service_time is strictly equal with the appear time
        double service_time = event_server_->get_service_time_(current_time_+1,input.mean_service_time);
        event_customer_->set_leaving_time_(current_time_,service_time);
        EventInFutureEventSet(event_customer_);
    }
    else{// BUSY
        if(event_server_->get_queue_length_()<input.maximum_queue_length){
            event_server_->CustomerInQueue(event_customer_);
            event_server_->IncreaseTotalCustomerServedNumber(); // everyone who successfully arrives should be counting in the total customer served number
        }
        else{
            std::cout<< "queue length too long, stop simulation.";
            exit(0);
        }
    }
}

void EventScheduler::Departure() {
    if((event_server_->get_queue_length_())==0){
        event_server_->set_server_status_(ServerStatus::IDLE);
    }
    else{
        event_server_->set_total_customer_waiting_time_(event_server_->GetCustomerGoingToDeparture());
        event_server_->CustomerOutQueue();
        if((event_server_->get_queue_length_())==0){
            event_server_->set_server_status_(ServerStatus::IDLE);
        }
        else{
            double service_time = event_server_->get_service_time_(current_time_,input.mean_service_time);
            Customer *customer_next_being_served = event_server_->GetCustomerNextBeingServed();
            customer_next_being_served->set_leaving_time_(current_time_,service_time);
            customer_next_being_served->set_server_(&(server_vec_.front()));
            EventInFutureEventSet(customer_next_being_served);
        }
    }
}

void EventScheduler::Process() {
    //TODO:: MMN modified choose server
    while(event_server_->get_total_customer_served_number_()<input.maximum_number_of_customer){
        set_event_customer_();
        set_event_server_();
        EventOutFutureEventSet();
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



