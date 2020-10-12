#include <iostream>

using namespace std;

class Foo
{
public:
    Foo ()
    {
        cout << "Foo's constructor" << endl;
    }
    ~Foo ()
    {
        cout << "Foo's destructor" << endl;
    }
};

class Bar : public Foo
{
public:
    Bar ()
    {
        cout << "Bar's constructor" << endl;
    }
    ~Bar ()
    {
        cout << "Bar's destructor" << endl;
    }
};

int main ()
{
    Bar bar;
}
