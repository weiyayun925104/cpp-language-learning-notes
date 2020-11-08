#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <cmath>

double hmean(double a, double b);
double gmean(double a, double b);

class bad_hmean : public std::invalid_argument
{
private:
    int arg1;
    int arg2;
public:
    bad_hmean(int a, int b, const std::string &s = "hmean(a, b) invalid arguments: a = -b\n") : std::invalid_argument(s), arg1(a), arg2(b) {}
    void display() const;
};

void bad_hmean::display() const
{
    std::cout << "For function hmean(a, b), a != -b" << std::endl;
    std::cout << "You entered a = " << arg1 << ", b = " << arg2 << std::endl;
}
class bad_gmean : public std::domain_error
{
private:
    int arg1;
    int arg2;
public:
    bad_gmean(int a, int b, const std::string &s = "gmean(a, b) arguments should be >= 0\n") : std::domain_error(s), arg1(a), arg2(b) {}
    void display() const;
};
void bad_gmean::display() const
{
    std::cout << "For function gmean(a, b), a >= 0 and b >= 0" << std::endl;
    std::cout << "You entered a = " << arg1 << ", b = " << arg2 << std::endl;
}

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
        catch (std::exception &e)
        {
            if (typeid(bad_hmean &) == typeid(e))
            {
                bad_hmean &bhm = dynamic_cast<bad_hmean &>(e);
                bhm.display();
            }
            else if(typeid(bad_gmean &) == typeid(e))
            {
                bad_gmean &bgm = dynamic_cast<bad_gmean &>(e);
                bgm.display();
            }
            cout << "Sorry, you don't get to play any more.\n";
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
        throw bad_hmean(a, b);
    }
    return (2.0 * a * b) / (a + b);
}

double gmean(double a, double b)
{
    if (a < 0 || b < 0)
    {
        throw bad_gmean(a, b);
    }
    return std::sqrt(a * b);
}
