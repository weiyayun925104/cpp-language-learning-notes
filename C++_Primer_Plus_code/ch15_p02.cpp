#include <iostream>
#include <stdexcept>
#include <cmath>

class bad_hmean : public std::logic_error
{
public:
    bad_hmean(const std::string &s = "hmean(a, b) invalid arguments: a = -b\n") : std::logic_error(s) {}
};

class bad_gmean : public std::logic_error
{
public:
    bad_gmean(const std::string &s = "gmean(a, b) arguments should be >= 0\n") : std::logic_error(s) {}
};

double hmean(double a, double b);
double gmean(double a, double b);

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    double x, y, z;

    cout << "Enter two numbers <q to quit>: ";
    while (cin >> x && cin >> y)
    {
        try
        {
            z = hmean(x, y);
            cout << "Harmonic mean of " << x << " and " << y
                 << " is " << z << endl;
            z = gmean(x, y);
            cout << "Geometric mean of " << x << " and " << y
                 << " is " << z << endl;
            cout << "Enter two numbers <q to quit>: ";
        }
        catch (bad_hmean &bg)
        {
            cout << bg.what();
            cout << "Enter two numbers <q to quit>: ";
            continue;
        }
        catch (bad_gmean &hg)
        {
            cout << hg.what();
            std::cout << "Sorry, you don't get to play any more.\n";
            break;
        }
    }
    cout << "Done.\n";

    return 0;
}

double hmean(double a, double b)
{
    if (a == -b)
    {
        throw bad_hmean();
    }
    return (2.0 * a * b) / (a + b);
}

double gmean(double a, double b)
{
    if (a < 0 || b < 0)
    {
        throw bad_gmean();
    }
    return std::sqrt(a * b);
}
