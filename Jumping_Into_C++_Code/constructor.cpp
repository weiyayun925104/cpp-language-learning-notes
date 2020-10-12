#include <iostream>

using namespace std;

class Foo
{
public:
    Foo ()
    {
        cout << "Foo's constructor" << endl;
    }
};

class Bar : public Foo
{
public:
    Bar ()
    {
        cout << "Bar's constructor" << endl;
    }
};

int main ()
{
    Bar bar;
}
