#include <iostream>

int enter_result(int golf_result[], int array_size);
double avg_result(int golf_result[], int array_size);
void output_result(double avg, int golf_result[], int array_size);

int main()
{
    const int SIZE = 10;

    int golf_result[SIZE] = { 0 };

    int num = enter_result(golf_result, SIZE);
    double avg = avg_result(golf_result, num);
    output_result(avg, golf_result, num);

    return 0;
}
int enter_result(int golf_result[], int array_size)
{
    std::cout << "Enter the results (1-10) or q to exit : " << std::endl;
    int i;
    for (i = 0; i < array_size; i++)
    {
        std::cout << "Result " << i + 1 << " : ";
        int enter = 0;

        if ( ! (std::cin >> enter) )
        {
            std::cin.clear();

            while (std::cin.get() != '\n')
            {
                continue;
            }
            std::cout << "Invalid Input.\n" << std::endl;
            break;
        }
        else if (enter < 1 || enter > 10)
        {
            while (std::cin.get() != '\n')
            {
                continue;
            }
            std::cout << "Input not in 1-10.\n" << std::endl;
            break;
        }
        golf_result[i] = enter;
    }
    return i;
}

double avg_result(int golf_result[], int array_size)
{
    double avg = 0;
    double summ = 0;

    for (int i = 0; i < array_size; i++)
    {
        summ += golf_result[i];
    }
    avg = summ / array_size;

    return avg;
}

void output_result(double avg, int golf_result[], int array_size)
{
    std::cout << "Result = ";

    for (int i = 0; i < array_size; i++)
    {
        std::cout << golf_result[i] << " ";
    }
    std::cout << "AVG = " << avg << std::endl;
}
