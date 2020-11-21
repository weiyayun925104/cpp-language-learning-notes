#include <iostream>
#include "student_info.h"
#include "grade.h"

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::vector;

bool compare(const Student_info &x, const Student_info &y)
{
    return x.name < y.name;
}

istream &read(istream &is, Student_info &s)
{
    cout << "Please enter your name: ";
    std::getline(is, s.name, '\n');
    if (is && s.name != "")
    {
        cout << "Please enter your midterm and final exam grades: ";
        is >> s.midterm >> s.final;
        cout << "Enter all your homework grades: ";
        read_hw(is, s.homework);
    }
    return is;
}

istream &read_hw(istream &is, vector<double> &hw)
{
    if (is)
    {
        double x;
        while (is >> x)
        {
            hw.push_back(x);
        }
        is.clear();
        while (is.get() != '\n')
        {
            continue;
        }
    }

    return is;
}
