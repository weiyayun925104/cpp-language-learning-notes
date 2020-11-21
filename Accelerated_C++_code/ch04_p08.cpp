#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

vector<double> f()
{
    return { 10.2, 17.5 };
}

int main()
{
    int n = 1;
    cout << f()[n] << endl;

    return 0;
}
