//
// Created by Zihao on 2020/3/6.
//

#ifndef MM1_PROJ_CUSTOMER_H
#define MM1_PROJ_CUSTOMER_H

#include <random>
class Customer {
public:
    // uses the default constructor and destructor.

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

    // Arrive event
    bool arrival();

    // Departure event
    bool departure();





private:
    double interarrival_time;
    double next_occurrence_time; // next_occurrence_time = realtime + interarrival_time
    double waiting_in_queue_time;
};


#endif //MM1_PROJ_CUSTOMER_H
