#include <iostream>
#include "sales_class.h"

SALES::Sales::Sales()
{
    for (int i = 0; i < QUARTERS; i++)
    {
        sales[i] = 0;
    }
    average = 0;
    max = 0;
    min = 0;
}
SALES::Sales::Sales(const double arr[], int n)
{
    for (int i = 0; i < QUARTERS; i++)
    {
        sales[i] = 0;
    }

    if (n > QUARTERS)
    {
        n = QUARTERS;
    }
    for (int i = 0; i < n; i++)
    {
        sales[i] = arr[i];
    }
    average = find_avg(sales, QUARTERS);
    max = find_max(sales, QUARTERS);
    min = find_min(sales, QUARTERS);
}
SALES::Sales::~Sales()
{

}

void SALES::Sales::setSales()
{
    for (int i = 0; i < QUARTERS; ++i)
    {
        std::cout << "Enter total sales for " << i + 1 << " quarter: ";
        std::cin >> sales[i];
    }

    average = find_avg(sales, QUARTERS);
    max = find_max(sales, QUARTERS);
    min = find_min(sales, QUARTERS);
}

void SALES::Sales::showSales()
{
    for (int i = 0; i < QUARTERS; i++)
    {
        if (i != 0)
        {
            std::cout << ", ";
        }
        std::cout << sales[i];
    }
    std::cout << std::endl;
    std::cout << "Average value: " << average << std::endl;
    std::cout << "Maximum value: " << max << std::endl;
    std::cout << "Minimum value: " << min << std::endl;
}
double SALES::Sales::find_avg(const double arr[], int size)
{
    double summ = 0;
    for (int i = 0; i < size; i++)
    {
        summ += arr[i];
    }
    return summ / size;
}

double SALES::Sales::find_max(const double arr[], int size)
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
double SALES::Sales::find_min(const double arr[], int size)
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
