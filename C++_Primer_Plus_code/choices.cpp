#include <iostream>
#include <vector>
#include <array>

using namespace std;

int main()
{

    double a1[4] = { 1.2, 2.4, 3.6, 4.8 };
    vector<double> a2(4);

    a2[0] = 1.0 / 3.0;
    a2[1] = 1.0 / 5.0;
    a2[2] = 1.0 / 7.0;
    a2[3] = 1.0 / 9.0;

    array<double, 4> a3 = { 3.14, 2.72, 1.62, 1.41 };
    array<double, 4> a4;
    a4 = a3;

    cout << "a1[0]: " << a1[0] << " at " << &a1[0] << endl;
    cout << "a2[0]: " << a2[0] << " at " << &a2[0] << endl;
    cout << "a3[0]: " << a3[0] << " at " << &a3[0] << endl;
    cout << "a4[0]: " << a4[0] << " at " << &a4[0] << endl;

    cout << "a1[1]: " << a1[1] << " at " << &a1[1] << endl;
    cout << "a2[1]: " << a2[1] << " at " << &a2[1] << endl;
    cout << "a3[1]: " << a3[1] << " at " << &a3[1] << endl;
    cout << "a4[1]: " << a4[1] << " at " << &a4[1] << endl;

    cout << "a1[2]: " << a1[2] << " at " << &a1[2] << endl;
    cout << "a2[2]: " << a2[2] << " at " << &a2[2] << endl;
    cout << "a3[2]: " << a3[2] << " at " << &a3[2] << endl;
    cout << "a4[2]: " << a4[2] << " at " << &a4[2] << endl;

    cout << "a1[3]: " << a1[3] << " at " << &a1[3] << endl;
    cout << "a2[3]: " << a2[3] << " at " << &a2[3] << endl;
    cout << "a3[3]: " << a3[3] << " at " << &a3[3] << endl;
    cout << "a4[3]: " << a4[3] << " at " << &a4[3] << endl;

    return 0;
}
