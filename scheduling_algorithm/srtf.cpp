#include <string_view>
#include <vector>
#include <queue>
#include <iomanip>
#include "../header_files/process.hpp"
#include "../header_files/display_table.hpp"

using namespace std;

void SRTF(vector<Process> &p, int64_t n);

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
    return 0;
}


void SRTF(vector<Process> &p, int64_t n)
{
    int64_t current_time{}, completed{};

    while (completed < n)
    {
        int idx = -1;

        for (size_t i{}; i < n; i++)
        {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && (idx == -1 || p[idx].remaining_time > p[i].remaining_time))
            {
                idx = i;
            }
        }

        if (idx != -1)
        {
            p[idx].remaining_time--;
            current_time++;
            if (p[idx].remaining_time == 0)
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
    display_average(p,n);
}