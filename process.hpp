#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include<stdlib.h>

class Process final
{

public:
    size_t id;
    static size_t next_id;
    int64_t arrival_time;
    int64_t burst_time;
    int64_t completion_time;
    int64_t remaining_time;
    int64_t turn_around_time;
    int64_t wait_time;

    Process()
    {
        std::cout << "Process Constructor Called :  ";
        id = next_id++;
        std::cout << id << std::endl;
    }

    Process(const Process &process)
    {
        std::cout << "PRocess Copy Constructor Called";
        id = next_id++;
        arrival_time = process.arrival_time;
        burst_time = process.burst_time;
        completion_time = process.completion_time;
        turn_around_time = process.turn_around_time;
        remaining_time = process.remaining_time;
        wait_time = process.wait_time;
        std::cout << std::endl;
    }

    Process &operator=(const Process &process)
    {
        if (this != &process)
        {
            this->arrival_time = process.arrival_time;
            this->burst_time = process.burst_time;
            this->completion_time = process.completion_time;
            this->remaining_time = process.remaining_time;
            this->turn_around_time = process.turn_around_time;
            this->wait_time = process.wait_time;
        }

        return *this;
    }

    ~Process()
    {
        std::cout << "Process Destructor Called" << std::endl;
    }
};

size_t Process::next_id = 0;

#endif