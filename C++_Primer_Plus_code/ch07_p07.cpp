#include <iostream>

const int Max = 5;

double *fill_array(double *arrBegin, double *arrEnd);
void show_array(double *arrBegin, double *arrEnd);
void revalue(double r, double *arrBegin, double *arrEnd);

int main()
{
    double properties[Max];
    double *size = fill_array(properties, properties + Max);
    show_array(properties, size);

    if ( (size - properties) > 0)
    {
        std::cout << "Enter revaluation factor: ";
        double factor = 0.0;
        while (!(std::cin >> factor))
        {
            std::cin.clear();
            while (std::cin.get() != '\n')
            {
                continue;
            }
            std::cout << "Bad input; Please enter a number: ";
        }
        revalue(factor, properties, size);
        show_array(properties, size);
    }
    std::cout << "Done.\n";

    return 0;
}

double *fill_array(double *arrBegin, double *arrEnd)
{
    double temp;
    int i = 0;
    double *pt = nullptr;

    for (pt = arrBegin; pt != arrEnd; pt++)
    {
        std::cout << "Enter value #" << (++i) << ": ";
        temp = 0;
        if ( ! (std::cin >> temp) )
        {
            std::cin.clear();
            while (std::cin.get() != '\n')
            {
                continue;
            }
            std::cout << "Bad input; input process terminated.\n";
            break;
        }
        else if (temp < 0)
        {
            while (std::cin.get() != '\n')
            {
                continue;
            }
            std::cout << "input process terminated.\n";
            break;
        }
        *pt = temp;
    }
    return pt;
}

void show_array(double *arrBegin, double *arrEnd)
{
    int i = 0;
    for (double *pt = arrBegin; pt != arrEnd; pt++)
    {
        std::cout << "Property #" << (++i) << ": $";
        std::cout << *pt << std::endl;
    }
}

void revalue(double factor, double *arrBegin, double *arrEnd)
{
    for (double *pt = arrBegin; pt != arrEnd; pt++)
    {
        *pt *= factor;
    }
}
