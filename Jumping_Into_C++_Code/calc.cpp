#include <iostream>

using namespace std;

template <typename Type>
class Calc
{
public:
    Calc ();
    Type multiply (Type x, Type y);
    Type add (Type x, Type y);
};

template <typename Type>
Calc<Type>::Calc () {}

template <typename Type>
Type Calc<Type>::multiply (Type x, Type y)
{
    return x * y;
}

template <typename Type>
Type Calc<Type>::add (Type x, Type y)
{
    return x + y;
}
int main ()
{
    Calc<int> c;
    cout << c.multiply(3, 6) << '\n';
    cout << c.add(3, 6) << '\n';

    return 0;
}
