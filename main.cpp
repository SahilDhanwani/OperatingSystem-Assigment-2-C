#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

class process
{
public:
    int id;
    int arrival_time;
    int init_burst_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turn_around_time;

    process() {}
    process(int a, int b, int c)
    {
        id = a;
        arrival_time = b;
        burst_time = c;
        completion_time = 0;
        waiting_time = 0;
        turn_around_time = 0;
        init_burst_time = burst_time;
    }
};

bool compareByArrivalTime(const process &p1, const process &p2)
{
    return p1.arrival_time < p2.arrival_time;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    process arr[n];

    for (int i = 0; i < n; i++)
    {
        int a, b, c;
        cout << "Enter the arrival time, and burst time of the process: ";
        cin >> b >> c;
        process p1(i + 1, b, c);
        arr[i] = p1;
    }

    int tq;
    cout << "Enter the Time Quantum (TQ): ";
    cin >> tq;

    sort(arr, arr + n, compareByArrivalTime);

    queue<int> ready_queue;

    int current_time = arr[0].arrival_time;
    int j = 1;
    ready_queue.push(0);
    int p2;
    while (ready_queue.size() != 0)
    {
        if (arr[ready_queue.front()].burst_time > tq)
        {
            current_time += tq;
            arr[ready_queue.front()].burst_time -= tq;
            process p2 = arr[ready_queue.front()]; // Change the variable type from int to process
        }

        else
        {
            current_time += min(tq, arr[ready_queue.front()].burst_time);
            arr[ready_queue.front()].burst_time = 0;
        }
        for (int i = j; i < n; i++)
        {
            if (arr[i].arrival_time <= current_time && arr[i].burst_time > 0)
            {
                ready_queue.push(i);
                j = i + 1;
            }
        }
        if (arr[ready_queue.front()].burst_time > 0)
        {
            p2 = ready_queue.front();
            ready_queue.pop();
            ready_queue.push(p2);
        }
        else
        {
            arr[ready_queue.front()].completion_time = current_time;
            arr[ready_queue.front()].turn_around_time = (current_time - arr[ready_queue.front()].arrival_time);
            arr[ready_queue.front()].waiting_time = (arr[ready_queue.front()].turn_around_time - arr[ready_queue.front()].init_burst_time);
            ready_queue.pop();
        }
    }

    float awt = 0;
    float att = 0;

    for (int i = 0; i < n; i++)
    {
        awt += arr[i].waiting_time;
        att += arr[i].turn_around_time;
    }

    awt = awt / n;
    att = att / n;

    cout << "The average waiting time (AWT) is : " << awt << endl;
    cout << "The average turnaround time (ATT) is : " << att;

    return 0;
}