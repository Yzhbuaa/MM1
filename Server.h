//
// Created by Zihao on 2020/3/9.
//

#ifndef QUEUE_MM1_SERVER_H
#define QUEUE_MM1_SERVER_H

#include <random>

class Server {
    // uses the default constructor and destructor.

public:
    enum ServerStatus{
        BUSY,
        IDLE
    };

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
    //          long double x = server1.ServiceTimeCalc(i,lambda);
    //          std::cout << x << std::endl;
    //          cnt+=x;
    //      }
    //      std::cout<< cnt/1000 <<std::endl; // approximately 3600
    double ServiceTimeCalc(const std::mt19937::result_type sd, const double lambda);

    // example:
//    Server server1;
//    server1.SetStatus(Server::ServerStatus::BUSY);
//    cout << "the server status is:" << server1.GetStatus() << endl;
    ServerStatus GetStatus(){return server_status_;}

    void SetStatus(ServerStatus ss){server_status_ = ss;}

private:
    ServerStatus server_status_;

};


#endif //QUEUE_MM1_SERVER_H
