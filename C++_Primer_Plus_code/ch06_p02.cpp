#include <iostream>

const int array_size = 10;

int main()
{
    double fond[array_size];
    double summ = 0.0;
    int count = 0;

    std::cout << "Enter 10 numbers of donations: " << std::endl;

    int i;
    for (i = 0; i < array_size; i++)
    {
        if ( ! (std::cin >> fond[i]) || fond[i] <= 0 )
        {
            break;
        }
        summ += fond[i];
    }

    double avg = summ / i;
    std::cout << "The average value of " << i << " donations: " << avg << std::endl;

    for (int j = 0; j < i; j++)
    {
        if (fond[j] > avg)
        {
            count++;
        }
    }
    std::cout << "Donations exceeding the average: " << count << std::endl;

    return 0;
}
