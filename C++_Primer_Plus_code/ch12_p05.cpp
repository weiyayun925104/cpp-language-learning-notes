#include <iostream>
#include <cstdlib>
#include <ctime>
#include "queue2.h"

const int MIN_PER_HR = 60;

bool newcustomer(double x);

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::ios_base;

    std::srand(std::time(nullptr));

    cout << "Case Study: Bank of Heather Automatic Teller\n";
    cout << "Enter maximum size of queue: ";
    int qs;
    cin >> qs;

    cout << "Enter the number of simulation hours: ";
    int hours;
    cin >> hours;
    long cyclelimit = MIN_PER_HR * hours;

    double perhour;
    double min_per_cust;

    Item temp;
    long turnaways = 0;
    long customers = 0;
    long served = 0;
    long sum_line = 0;
    int wait_time = 0;
    long line_wait = 0;

    int i = hours;

    do
    {
        perhour = i--;
        min_per_cust = MIN_PER_HR / perhour;
        Queue line(qs);
        turnaways = 0;
        customers = 0;
        served = 0;
        sum_line = 0;
        wait_time = 0;
        line_wait = 0;

        for (long cycle = 0; cycle < cyclelimit; cycle++)
        {
            if (newcustomer(min_per_cust))
            {
                if (line.isfull())
                {
                    turnaways++;
                }
                else
                {
                    customers++;
                    temp.set(cycle);
                    line.enqueue(temp);
                }
            }
            if (wait_time <= 0 && !line.isempty())
            {
                line.dequeue(temp);
                wait_time = temp.ptime();
                line_wait += cycle - temp.when();
                served++;
            }
            if (wait_time > 0)
            {
                wait_time--;
            }
            sum_line += line.queuecount();
        }
    }
    while ((double)line_wait / served > 1.0);
    i++;

    if (customers > 0)
    {
        std::cout << "customers per hours: " << i << std::endl;
        cout << "customers accepted: " << customers << endl;
        cout << "customers served: " << served << endl;
        cout << "customers turnaways: " << turnaways << endl;
        cout.precision(2);
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout.setf(ios_base::showpoint);
        cout << "average queue size: " << (double)sum_line / cyclelimit << endl;
        cout << "average wait time: " << (double)line_wait / served << " minutes\n";
    }
    else
    {
        cout << "No customers!\n";
    }
    cout << "Done.\n";

    return 0;
}
bool newcustomer(double x)
{
    return ( (std::rand() * x) / RAND_MAX < 1);
}
