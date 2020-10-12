
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename  Type>
class VectorSum
{
public:
    VectorSum();
    Type sum(const std::vector<Type> &vector);
};

template <typename Type>
VectorSum<Type>::VectorSum()
{
}

template <typename Type>
Type VectorSum<Type>::sum(const std::vector<Type> &vector)
{
    Type sum = 0;
    for (typename std::vector<Type>::const_iterator itr = vector.begin(), end = vector.end(); itr != end; ++itr)
    {
        sum += *itr;
    }

    return sum;
}

int main()
{
    vector<int> vectorInt;

    vectorInt.push_back(5);
    vectorInt.push_back(4);
    vectorInt.push_back(3);
    vectorInt.push_back(2);
    vectorInt.push_back(1);
    vectorInt.push_back(0);

    VectorSum<int> calcInt;

    cout << "Integer type:\n";
    cout << "Sum(vector) = " << calcInt.sum(vectorInt) << '\n';

    vector<double> vectorDbl;

    vectorDbl.push_back(5.5);
    vectorDbl.push_back(4.4);
    vectorDbl.push_back(3.3);
    vectorDbl.push_back(2.2);
    vectorDbl.push_back(1.1);
    vectorDbl.push_back(0);

    VectorSum<double> calcDbl;

    cout << "Double type:\n";
    cout << "Sum(vector) = " << calcDbl.sum(vectorDbl) << '\n';
}
