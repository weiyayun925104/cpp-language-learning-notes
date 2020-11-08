#include <iostream>

using namespace std;

struct inflatable
{
    char name[32];
    double volume;
    double price;
};

int main()
{
    inflatable *ps = new inflatable;
    cout << "Enter name of inflatable item: ";
    cin.getline(ps->name, 32);
    cout << "Enter volume in cubic feet: ";
    cin >> (*ps).volume;
    cout << "Enter price: $";
    cin >> ps->price;
    cout << "Name: " << (*ps).name << endl;
    cout << "Volume: " << ps->volume << " cubic feet\n";
    cout << "Price: $" << ps->price << endl;
    delete ps;

    return 0;
}
