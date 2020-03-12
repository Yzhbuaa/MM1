#include <iostream>
#include "Customer.h"
#include "Server.h"
#include "EventScheduler.h"
#include <vector>

using std::cout;
using std::cin;
using std::endl;


int main() {

    Input input;
    // input
    cout << "Please enter server number, mean interarrival time, mean service time, \nmaximum number of customer, and maximum queue length:" << endl;
    cin >> input.server_number >>input.mean_interarrival_time>>input.mean_service_time>>input.maximum_number_of_customer>>input.maximum_queue_length;

    // initialize (the constructors of class EventScheduler, Server, and Customer does most of the initialization work.
    EventScheduler event_scheduler;
    event_scheduler.Initialize(input);
    event_scheduler.Process();

    return 0;
}
