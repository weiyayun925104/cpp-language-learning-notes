#include <iostream>

long double probability(int numbers, int picks);

int main()
{
    double total1 = 0;
    double total2 = 0;
    double choices = 0;

    std::cout << "Enter the total number of choices on the game card and\n";
    std::cout << "the number of picks allowed and\n";
    std::cout << "the total number of choices on the second game field\n";

    while ( (std::cin >> total1) && (std::cin >> choices) && choices <= total1 && (std::cin >> total2) )
    {
        std::cout << "You have one chance in " << probability(total1, choices) * probability(total2, 1) << " of winning.\n";
        std::cout << "Next two numbers (q to quit) : ";
    }
    std::cout << "Done.\n";

    return 0;
}
long double probability(int numbers, int picks)
{
    long double result = 1.0;
    long double n;
    int p;
    for (n = numbers, p = picks; p > 0; n--, p--)
    {
        result = result * n / p;
    }
    return result;
}
