#include <iostream>

struct debts
{
    char name[128];
    double amount;
};

template <typename T>
T SumArray(T arr[], int n);
template <typename T>
T SumArray(T *arr[], int n);
template <typename T>
void ShowArray(T arr[], int n);
template <typename T>
void ShowArray(T *arr[], int n);

int main()
{
    int things[6] = { 13, 31, 103, 301, 310, 130 };
    debts mr_E[3] =
    {
        { "Ima Wolfe", 2400.0 },
        { "Ura Foxe", 1300.0 },
        { "Iby Stout", 1800.0 }
    };

    double *pd[3];

    for (int i = 0; i < 3; i++)
    {
        pd[i] = &(mr_E[i].amount);
    }

    std::cout << "Listing Mr. E's counts of things :\n";
    ShowArray(things, 6);
    std::cout << "Total = " << SumArray(things, 6) << std::endl;

    std::cout << "Listing Mr. E's debts:\n";
    ShowArray(pd, 3);
    std::cout << "Total = " << SumArray(pd, 3) << std::endl;

    return 0;
}

template <typename T>
T SumArray(T arr[], int n)
{
    T summ = 0;
    for (int i = 0; i < n; i++)
    {
        summ += arr[i];
    }
    return summ;
}

template <typename T>
T SumArray(T *arr[], int n)
{
    T summ = 0;
    for (int i = 0; i < n; i++)
    {
        summ += *arr[i];
    }
    return summ;
}

template <typename T>
void ShowArray(T arr[], int n)
{
    std::cout << "template ShowArray A\n";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

template <typename T>
void ShowArray(T *arr[], int n)
{
    std::cout << "template ShowArray B\n";
    for (int i = 0; i < n; i++)
    {
        std::cout << *arr[i] << ' ';
    }
    std::cout << std::endl;
}
