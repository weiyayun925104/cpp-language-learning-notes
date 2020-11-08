#include <iostream>

int main()
{
    std::cout << "Enter the number of earned tvarpov: ";
    double twarp = 0;

    while (std::cin >> twarp && twarp >= 0)
    {
        double summ = 0;

        if (twarp <= 5000)
        {
            std::cout << "Your tax = 0" << std::endl;
        }
        else if ((twarp > 5000) && (twarp <= 15000))
        {
            summ = (5000 * 0) + ((twarp - 5000) * 0.10);
            std::cout << "Your tax = " << summ << std::endl;
        }
        else if ((twarp > 15000) && (twarp <= 35000))
        {
            summ = (5000 * 0) + (10000 * 0.10) + ((twarp - 15000) * 0.15);
            std::cout << "Your tax = " << summ << std::endl;
        }
        else if (twarp > 35000)
        {
            summ = (5000 * 0) + (10000 * 0.10) + (20000 * 0.15) + ((twarp - 35000) * 0.20);
            std::cout << "Your tax = " << summ << std::endl;
        }
        std::cout << "Enter the number of earned tvarpov: ";
    }

    return 0;
}
