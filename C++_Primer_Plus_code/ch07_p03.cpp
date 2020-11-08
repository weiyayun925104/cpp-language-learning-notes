#include <iostream>

using namespace std;

struct box
{
    char maker[128];
    double height;
    double width;
    double length;
    double volume;
};

void print_box(const box details);
void set_volume(box *address);

int main()
{
    box details;
    cout << "Enter maker : ";
    cin.get(details.maker, 128);

    while (cin.get() != '\n')
    {
        continue;
    }

    cout << "Enter height : ";
    cin >> details.height;
    cout << "Enter width : ";
    cin >> details.width;
    cout << "Enter length : ";
    cin >> details.length;

    set_volume(&details);
    cout << '\n';
    print_box(details);

    return 0;
}

void print_box(const box details)
{
    cout << "maker = " << details.maker << endl;
    cout << "height = " << details.height << endl;
    cout << "width = " << details.width << endl;
    cout << "length = " << details.length << endl;
    cout << "volume = " << details.volume << endl;
}

void set_volume(box *address)
{
    address->volume = (address->height) * (address->length) * (address->width);
}
