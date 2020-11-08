#include <iostream>

const int SIZE = 10;

int fill_array(double massiv[], int size);
void Show_array(double massiv[], int size);
void Reverse_array(double massiv[], int size);

int main()
{
    double massiv[SIZE] = { 0 };

    int num = fill_array(massiv, SIZE);
    Show_array(massiv, num);
    std::cout << '\n';
    Reverse_array(massiv, num);
    Show_array(massiv, num);
    std::cout << '\n';
    Reverse_array(massiv + 1, num - 2);
    Show_array(massiv, num);

    return 0;
}

int fill_array(double massiv[], int size)
{
    double number;
    int i;
    for (i = 0; i < size; i++)
    {
        std::cout << "Value " << i + 1 << " = ";
        number = 0;
        if ( ! (std::cin >> number) )
        {
            break;
        }
        massiv[i] = number;
    }
    return i;
}

void Reverse_array(double massiv[], int size)
{
    for (int i = 0, j = size - 1; i < j; i++, j--)
    {
        double temp = 0;

        temp = massiv[i];
        massiv[i] = massiv[j];
        massiv[j] = temp;
    }
}

void Show_array(double massiv[], int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << massiv[i] << std::endl;
    }
}
