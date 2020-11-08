#include <iostream>

template <typename T>
T max5(T *massiv);

int main()
{
    double double_massiv[5] = { 0.1, 1.2, 3.45, 2.2, 1.3 };
    std::cout << "Maximum value of the array double = ";
    std::cout << max5(double_massiv) << std::endl;

    int int_massiv[5] = { 2, 5, 8, 66, 231 };
    std::cout << "Maximum value of array int = ";
    std::cout << max5(int_massiv) << std::endl;

    return 0;
}

template <typename T>
T max5(T *massiv)
{
    T max = massiv[0];
    for (int i = 0; i < 5; i++)
    {
        if (massiv[i] > max)
        {
            max = massiv[i];
        }
    }
    return max;
}
