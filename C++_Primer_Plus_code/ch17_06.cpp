#include <iostream>
#include <iomanip>

int main()
{
    using namespace std;
    cout << "Enter an integer: ";
    int n;
    cin >> n;
    cout << setw(15) << "base ten" << setw(15) << "base sixteen" << setw(15) << "base eight" << endl;
    cout << showbase << setw(15) << n << hex << setw(15) << n << oct << setw(15) << n << endl;

    return 0;
}
