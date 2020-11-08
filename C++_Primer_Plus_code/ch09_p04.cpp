#include <iostream>
#include "sales.h"

int main()
{
    SALES::Sales struct1;
    SALES::setSales(struct1);
    std::cout << std::endl;
    SALES::showSales(struct1);

    std::cout << std::endl;

    double arr[] = { 123.12, 522.22, 455.42, 777.32 };
    SALES::Sales struct2;
    SALES::setSales(struct2, arr, SALES::QUARTERS);
    SALES::showSales(struct2);

    return 0;
}
