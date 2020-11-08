#include <iostream>
#include "sales_class.h"

int main()
{
    double arr[] = { 123.12, 522.22, 455.42, 777.32 };

    SALES::Sales Struct1;
    Struct1.setSales();
    std::cout << std::endl;
    Struct1.showSales();
    std::cout << std::endl;

    SALES::Sales Struct2 (arr, SALES::QUARTERS);
    Struct2.showSales();

    return 0;
}
