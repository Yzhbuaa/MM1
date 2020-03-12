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
    cout << "Please enter server number, mean interarrival time(s), mean service time(s), \nmaximum number of customer, and maximum queue length:" << endl;
    cin >> input.server_number >>input.mean_interarrival_time>>input.mean_service_time>>input.maximum_number_of_customer>>input.maximum_queue_length;

//    input.server_number=1;
//    input.mean_interarrival_time=30;
//    input.mean_service_time = 30;
//    input.maximum_number_of_customer =100;
//    input.maximum_queue_length =100;
    EventScheduler event_scheduler;
    event_scheduler.Initialize(input);
    event_scheduler.Process();
    event_scheduler.PrintOutStatistics();

    return 0;
}
