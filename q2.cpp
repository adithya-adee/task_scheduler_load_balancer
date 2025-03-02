#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include "process.hpp"

using namespace std;

void display_table(vector<Process> p,int64_t n)
{
    cout << "+------------+--------------+------------+-----------------+--------------+-----------------+"<<endl;
    cout << "| Process ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time |" << endl;
    cout << "+------------+--------------+------------+-----------------+--------------+-----------------+"<<endl;

    for (const auto &x : p)
    {
        cout << "| " << setw(10) << x.id << " | "
             << setw(12) << x.arrival_time << " | " 
             << setw(10) << x.burst_time << " | "
             << setw(15) << x.completion_time << " | "
             << setw(12) << x.wait_time << " | "
             << setw(15) << x.turn_around_time << " |" << endl;
    }

    cout << "+------------+--------------+------------+-----------------+--------------+-----------------+" << endl;
}

void display_average(vector<Process> p,int64_t n)
{
    double total_wt = 0, total_tat = 0;
    for (const auto &x : p)
    {
        total_tat += x.turn_around_time;
        total_wt += x.wait_time;
    }
    cout << "Average Turnaround Time: " << total_tat / n << " Average Waiting Time: " << total_wt / n << endl;
}

void SRTF(std::vector<Process> p,int64_t n)
{
    int64_t current_time{}, completed{};

    while (completed < n)
    {
        int64_t index = -1;

        for (int64_t i{}; i < n; i++)
        {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && (index == -1 || p[i].remaining_time < p[index].remaining_time))
            {
                index = i;
            }
        }

        if (index != -1)
        {
            p[index].remaining_time--;
            current_time++;
            if (p[index].remaining_time == 0)
            {
                p[index].completion_time = current_time;
                p[index].turn_around_time = p[index].completion_time - p[index].arrival_time;
                p[index].wait_time = p[index].turn_around_time - p[index].burst_time;
                completed++;
            }
        }
        else
        {
            current_time++;
        }
    }

    display_table(p, n);
    display_average(p, n);
}

void RR(vector<Process> &p,int64_t n,int64_t tq)
{
    queue<int64_t> q;
    vector<bool> visited(n, false);
   int64_t current_time = 0, completed = 0;

    q.push(0);
    visited[0] = true;

    while (completed < n)
    {
        if (!q.empty())
        {
           int64_t index = q.front();
            q.pop();

           int64_t exec_time = min(tq, p[index].remaining_time);
            p[index].remaining_time -= exec_time;
            current_time += exec_time;

            for (int64_t i = 0; i < n; i++)
            {
                if (!visited[i] && p[i].arrival_time <= current_time && p[i].remaining_time > 0)
                {
                    q.push(i);
                    visited[i] = true;
                }
            }

            if (p[index].remaining_time > 0)
            {
                q.push(index);
            }
            else
            {
                p[index].completion_time = current_time;
                p[index].turn_around_time = p[index].completion_time - p[index].arrival_time;
                p[index].wait_time = p[index].turn_around_time - p[index].burst_time;
                completed++;
            }
        }
        else
        {
            current_time++;
        }
    }

    display_table(p, n);
    display_average(p, n);
}

int main()
{
   int64_t n, tq;
    cout << "Enter the time quantum: ";
    cin >> tq;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int64_t i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    SRTF(processes, n);
    RR(processes, n, tq);
    return 0;
}
