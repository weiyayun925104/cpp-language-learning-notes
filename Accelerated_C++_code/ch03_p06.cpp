#include <iostream>
#include <string>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::streamsize;
using std::string;
using std::setprecision;

void StudentGradeAverageRobust()
{
    cout << "Please enter your name: ";
    string name;
    std::getline(cin, name, '\n');
    cout << "Hello, " << name << "!" << endl;

    cout << "Please enter your midterm and final exam grades: ";
    double midterm, final;
    cin >> midterm >> final;

    cout << "Enter all your homework grades, "
         "followed by end-of-file: ";

    int count = 0;
    double sum = 0;
    double x;

    while (cin >> x)
    {
        ++count;
        sum += x;
    }
    cin.clear();
    while (cin.get() != '\n')
    {
        continue;
    }

    double homework = count == 0 ? 0 : sum / count;

    streamsize prec = cout.precision();
    cout << "Your final grade is " << setprecision(3)
         << 0.2 * midterm + 0.4 * final + 0.4 * homework
         << setprecision(prec) << endl;
}

int main()
{
    cout << std::fixed;
    StudentGradeAverageRobust();

    return 0;
}
