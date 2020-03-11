#include <iostream>
#include "Customer.h"
#include "Server.h"
#include "EventScheduler.h"

using std::cout;
using std::cin;
using std::endl;



struct Input{

    Input():server_number(0), mean_interarrival_time(0), mean_service_time(0),
    maximum_number_of_customer(0),maximum_queue_length(0){}

    int server_number;
    double mean_interarrival_time;
    double mean_service_time;
    int maximum_number_of_customer;
    int maximum_queue_length;

} input;

int main() {

    // input
    cout << "Please enter server number, mean interarrival time, mean service time, \nmaximum number of customer, and maximum queue length:" << endl;
    cin >> input.server_number >>input.mean_interarrival_time>>input.mean_service_time>>input.maximum_number_of_customer>>input.maximum_queue_length;

    // initialize (the constructors of class EventScheduler, Server, and Customer does most of the initialization work.
    EventScheduler event_scheduler;
    Server server;
    Customer customer_0(server, event_scheduler.get_current_time_(), input.mean_interarrival_time);
    customer_0.set_appear_time_(event_scheduler.get_current_time_());
    event_scheduler.EventInFutureEventList(&customer_0);

    // process
    while(server.GetTotalCustomerServedNumber() < input.maximum_number_of_customer){



    }











//    cin >> server_number >> ;
//    if(server_number != 1){
//        cout << "error" <<endl;
//        return 0;
//    }







    return 0;
}
