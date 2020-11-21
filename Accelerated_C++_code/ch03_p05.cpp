#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::streamsize;
using std::vector;
using std::string;
using std::setprecision;

int StudentGradeAverage(double &result, string &name)
{
    cout << "Please enter your name: ";
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

    result = 0.2 * midterm + 0.4 * final + 0.4 * homework;

    return 0;
}

void OuputGradeAverage(double grade)
{
    streamsize prec = cout.precision();
    cout << "Your final grade is " << setprecision(3)
         << grade << setprecision(prec) << endl;
}

int StudentNamesGrades()
{
    vector<string> names;
    vector<double> grades;
    string answer;
    bool finish;

    do
    {
        string name;
        double grade;
        if (StudentGradeAverage(grade, name))
        {
            return 1;
        }

        names.push_back(name);
        grades.push_back(grade);

        cout << "Enter (y)es if you want to enter more grades and students: ";
        std::getline(cin, answer, '\n');
        if ( answer.size() > 0 && (answer.at(0) == 'y' || answer.at(0) == 'Y') )
        {
            finish = false;
            cout << endl;
        }
        else
        {
            finish = true;
        }
    }
    while (finish == false);

    cout << endl;
    for (vector<string>::size_type i = 0; i < names.size(); i++)
    {
        cout << names[i] << ":" << endl;
        OuputGradeAverage(grades[i]);
    }

    return 0;
}

int main()
{
    return StudentNamesGrades();
}
