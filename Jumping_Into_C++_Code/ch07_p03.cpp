#include <iostream>
#include <string>

using namespace std;

bool isDivisible(int number, int divisor);
bool isPrime(int number);
int getPrimeFactor(int number);
string numberHasPrimeFactorsWhichSumToPrime(int number);

int main()
{
    for (size_t i = 1; i <= 1000; i++)
    {
        string message = numberHasPrimeFactorsWhichSumToPrime(i);
        if (!(message == ""))
        {
            cout << message;
        }
    }
}

bool isPrime(int number)
{
    if (number <= 1)
    {
        return false;
    }

    int prime = 2;
    if (number == prime)
    {
        return true;
    }
    if (isDivisible(number, prime))
    {
        return false;
    }
    prime = 3;
    if (number == prime)
    {
        return true;
    }
    if (isDivisible(number, prime))
    {
        return false;
    }
    prime = 5;
    if (number == prime)
    {
        return true;
    }
    if (isDivisible(number, prime))
    {
        return false;
    }
    prime = 7;
    if (number == prime)
    {
        return true;
    }
    if (isDivisible(number, prime))
    {
        return false;
    }

    for (int i = 2; (i * i) <= number; i++)
    {
        if (isDivisible(number, i))
        {
            return false;
        }
    }
    return true;
}

bool isDivisible(int number, int divisor)
{
    return  number % divisor == 0;
}

int getPrimeFactor(int number)
{
    if (number <= 1)
    {
        return 0;
    }

    for (int i = 2; (i * i) <= number; i++)
    {
        if (isDivisible(number, i) && isPrime(i))
        {
            return i;
        }
    }
    return 0;
}

string numberHasPrimeFactorsWhichSumToPrime(int number)
{
    if (number <= 1)
    {
        return "";
    }
    if (isPrime(number))
    {
        return to_string(number) + " is prime number. \n";
    }

    int remainder = number;
    int currentSum = 0;
    string message = to_string(number) + " has prime factors: ";
    bool isFirstTerm = true;
    while (true)
    {
        int primeFactor = getPrimeFactor(remainder);
        if (primeFactor == 0)
        {
            return "An error has occurred with number " + to_string(number) + "\n";
        }
        if (!isFirstTerm)
        {
            message += ", ";
        }
        message += to_string(primeFactor);

        currentSum += primeFactor;
        remainder = (remainder / primeFactor);

        if (isPrime(remainder))
        {
            if (isPrime(remainder + currentSum))
            {
                message += ", " + to_string(remainder);
                message += " Which sum to: " + to_string(remainder + currentSum) + "\n";
                return message;
            }
            return "";
        }
        isFirstTerm = false;
    }
    return "";
}
