//
// Created by Zihao on 2020/3/6.
//

#ifndef MM1_PROJ_CUSTOMER_H
#define MM1_PROJ_CUSTOMER_H

#include <random>
class Customer {

public:
    // using default constructor and destructor

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
    //          long double x = customer1.interarrival_time_calculator(i,lambda);
    //          std::cout << x << std::endl;
    //          cnt+=x;
    //      }
    //      std::cout<< cnt/1000 <<std::endl; // approximately 3600
    double interarrival_time_calculator(const std::mt19937::result_type sd, const double lambda);

    // Arrive event of this Customer
    bool arrival();

    // Departure event of this Customer
    bool departure();





private:
    double interarrival_time; // interarrival time of this Customer
    double next_occurrence_time; // next_occurrence_time = realtime + interarrival_time
};


#endif //MM1_PROJ_CUSTOMER_H
