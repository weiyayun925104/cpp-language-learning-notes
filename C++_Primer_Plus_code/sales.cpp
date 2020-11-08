#include <iostream>
#include "sales.h"

void SALES::setSales(Sales &s, const double arr[], int n)
{
    if (n > QUARTERS)
    {
        n = QUARTERS;
    }

    for (int i = 0; i < n; i++)
    {
        s.sales[i] = arr[i];
    }
    s.average = find_avg(s.sales, QUARTERS);
    s.max = find_max(s.sales, QUARTERS);
    s.min = find_min(s.sales, QUARTERS);
}

void SALES::setSales(Sales &s)
{
    for (int i = 0; i < QUARTERS; ++i)
    {
        std::cout << "Enter sales for quarter " << i + 1 << '\n';
        std::cin >> s.sales[i];
    }

    s.average = find_avg(s.sales, QUARTERS);
    s.max = find_max(s.sales, QUARTERS);
    s.min = find_min(s.sales, QUARTERS);
}

void SALES::showSales(const Sales &s)
{
    for (int i = 0; i < QUARTERS; i++)
    {
        if (i != 0)
        {
            std::cout << ", ";
        }
        std::cout << s.sales[i];
    }
    std::cout << std::endl;
    std::cout << "average: " << s.average << std::endl;
    std::cout << "max: " << s.max << std::endl;
    std::cout << "min: " << s.min << std::endl;
}

double find_avg(const double arr[], int size)
{
    double summ = 0;
    for (int i = 0; i < size; i++)
    {
        summ += arr[i];
    }
    return summ / size;
}

double find_max(const double arr[], int size)
{
    double max = arr[0];
    for (int i = 0; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

double find_min(const double arr[], int size)
{
    double min = arr[0];
    for (int i = 0; i < size; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}
