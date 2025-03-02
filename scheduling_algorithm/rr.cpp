#include <string_view>
#include <vector>
#include <queue>
#include <iomanip>
#include "../header_files/process.hpp"
#include "../header_files/display_table.hpp"

using namespace std;

void RR(vector<Process> &p, int64_t n, int64_t tq);

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

    RR(processes, n, tq);
    return 0;
}

void RR(vector<Process> &p, int64_t n, int64_t tq)
{
    queue<int64_t> q;
    vector<bool> visited(n, false);
    int64_t current_time{}, completed{};

    q.push(0);
    visited[0] = true;

    while (completed < n)
    {
        if (!q.empty())
        {
            int64_t idx = q.front();
            q.pop();

            int64_t execution_time = min(tq, p[idx].remaining_time);
            p[idx].remaining_time -= execution_time;
            current_time += execution_time;

            for (size_t i{}; i < n; i++)
            {
                if (!visited[i] && p[i].remaining_time > 0 && p[i].arrival_time <= current_time)
                {
                    q.push(i);
                    visited[i] = true;
                }
            }

            if (p[idx].remaining_time > 0)
            {
                q.push(idx);
            }
            else
            {
                p[idx].completion_time = current_time;
                p[idx].turn_around_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].wait_time = p[idx].turn_around_time - p[idx].burst_time;
                completed++;
            }
        }
        else
        {
            current_time++;
        }
    }
    display_table(p,n);
    display_average(p, n);
}