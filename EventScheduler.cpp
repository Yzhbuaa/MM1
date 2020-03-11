//
// Created by Zihao on 2020/3/6.
//

#include "EventScheduler.h"

Customer* EventScheduler::select_event() {
    for(auto itr = future_event_set_.cbegin(); itr != future_event_set_.cend(); ++itr){
        return (*itr);
    }

}





