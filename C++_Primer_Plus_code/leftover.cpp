#include <iostream>

using namespace std;

long long left(long long num, int ct);
char *left(const char *str, int n = 1);

int main()
{
    const char *trip = "abcdefghijkl";
    long long n = 123456789876;
    int i;
    char *temp;
    for (i = 1; i < 10; i++)
    {
        cout << left(n, i) << endl;
        temp = left(trip, i);
        cout << temp << endl;
        delete[] temp;
    }

    return 0;
}

long long left(long long num, int ct)
{
    if (ct <= 0 || num <= 0)
    {
        return 0;
    }
    int digits = 1;
    long long n = num;
    while (n /= 10)
    {
        digits++;
    }
    if (digits > ct)
    {
        ct = digits - ct;
        while (ct--)
        {
            num /= 10;
        }
        return num;
    }
    else
    {
        return num;
    }
}
char *left(const char *str, int n)
{
    if (n < 1)
    {
        n = 1;
    }
    char *p = new char[n + 1];
    int i;
    for (i = 0; i < n && str[i]; i++)
    {
        p[i] = str[i];
    }
    while (i <= n)
    {
        p[i++] = '\0';
    }
    return p;
}
