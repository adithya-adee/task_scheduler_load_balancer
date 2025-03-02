#ifndef DISPLAY_TABLE_HPP
#define DISPLAY_TABLE_HPP

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "process.hpp"
#include <iomanip>

inline void display_table (std::vector<Process> p, int64_t n)
{
    std::cout << "+------------+--------------+------------+-----------------+--------------+-----------------+" << std::endl;
    std::cout << "| Process ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time |" << std::endl;
    std::cout << "+------------+--------------+------------+-----------------+--------------+-----------------+" << std::endl;

    for (const auto &x : p)
    {
        std::cout << "| " << std::setw(10) << x.id << " | "
             << std::setw(12) << x.arrival_time << " | "
             << std::setw(10) << x.burst_time << " | "
             << std::setw(15) << x.completion_time << " | "
             << std::setw(12) << x.wait_time << " | "
             << std::setw(15) << x.turn_around_time << " |" << std::endl;
    }

    std::cout << "+------------+--------------+------------+-----------------+--------------+-----------------+" << std::endl;
}

inline void display_average(std::vector<Process> &p, int64_t n)
{
    double total_wt = 0, total_tat = 0;
    for (const auto &x : p)
    {
        total_tat += x.turn_around_time;
        total_wt += x.wait_time;
    }
    std::cout << "Average Turnaround Time: " << total_tat / n << " Average Waiting Time: " << total_wt / n << std::endl;
}


#endif