#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

double average(const vector<double> &nums)
{
    double sum = 0;

    for (vector<double>::size_type i = 0; i < nums.size(); i++)
    {
        sum += nums[i];
    }

    return sum / nums.size();
}

int main()
{
    vector<double> numbers = { 10.2, 15.7, 18.5, 9.7, 25.2 };
    cout << average(numbers) << endl;

    return 0;
}
