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

    long turnawaysL1 = 0;
    long customersL1 = 0;
    long servedL1 = 0;
    long sum_lineL1 = 0;
    int wait_timeL1 = 0;
    long line_waitL1 = 0;

    long turnawaysL2 = 0;
    long customersL2 = 0;
    long servedL2 = 0;
    long sum_lineL2 = 0;
    int wait_timeL2 = 0;
    long line_waitL2 = 0;

    double average_wait;


    int i = hours;

    do
    {
        perhour = i--;
        min_per_cust = MIN_PER_HR / perhour;
        Queue line1(qs);
        Queue line2(qs);
        turnawaysL1 = turnawaysL2 = 0;
        customersL1 = customersL2 = 0;
        servedL1 = servedL2 = 0;
        sum_lineL1 = sum_lineL2 = 0;
        wait_timeL1 = wait_timeL2 = 0;
        line_waitL1 = line_waitL2 = 0;

        for (long cycle = 0; cycle < cyclelimit; cycle++)
        {
            if (newcustomer(min_per_cust))
            {
                if (line1.queuecount() <= line2.queuecount())
                {
                    if (line1.isfull())
                    {
                        turnawaysL1++;
                    }
                    else
                    {
                        customersL1++;
                        temp.set(cycle);
                        line1.enqueue(temp);
                    }
                }
                else
                {
                    if (line2.isfull())
                    {
                        turnawaysL2++;
                    }
                    else
                    {
                        customersL2++;
                        temp.set(cycle);
                        line2.enqueue(temp);
                    }
                }
            }
            if (wait_timeL1 == 0 && !line1.isempty())
            {
                line1.dequeue(temp);
                wait_timeL1 = temp.ptime();
                line_waitL1 += cycle - temp.when();
                servedL1++;
            }

            if (wait_timeL2 == 0 && !line2.isempty())
            {
                line2.dequeue(temp);
                wait_timeL2 = temp.ptime();
                line_waitL2 += cycle - temp.when();
                servedL2++;
            }
            if (wait_timeL1 > 0)
            {
                wait_timeL1--;
            }

            if (wait_timeL2 > 0)
            {
                wait_timeL2--;
            }
            sum_lineL1 += line1.queuecount();
            sum_lineL2 += line2.queuecount();
        }
        average_wait = double(line_waitL1 + line_waitL2) / (servedL1 + servedL2);

    }
    while (average_wait > 1.0);
    i++;

    if (customersL1 + customersL2 > 0)
    {
        std::cout << "customers per hours: " << i << std::endl;
        cout << "customers accepted: " << customersL1 + customersL2 << endl;
        cout << "customers served: " << servedL1 + servedL2 << endl;
        cout << "customers turnaways: " << turnawaysL1 + turnawaysL2 << endl;
        cout.precision(2);
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout.setf(ios_base::showpoint);
        cout << "average queue1 size: " << (double)sum_lineL1 / cyclelimit << endl;
        cout << "average queue2 size: " << (double)sum_lineL2 / cyclelimit << endl;
        cout << "average queue size: " << ( (double)(sum_lineL1 * sum_lineL2) / (sum_lineL1 + sum_lineL2) ) / cyclelimit << endl;
        cout << "average wait time: " << average_wait << " minutes\n";
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
