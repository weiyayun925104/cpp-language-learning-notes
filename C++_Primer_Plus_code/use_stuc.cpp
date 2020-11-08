#include <iostream>
#include "studentc.h"

using std::cin;
using std::cout;
using std::endl;

const int pupils = 3;
const int quizzes = 5;

void set(Student &sa, int n);

int main()
{
    Student ada[pupils] = { Student(quizzes), Student(quizzes), Student(quizzes) };

    int i;
    for (i = 0; i < pupils; ++i)
    {
        set(ada[i], quizzes);
    }
    cout << endl;
    cout << "Student List:\n";
    for (i = 0; i < pupils; ++i)
    {
        cout << ada[i].Name() << endl;
    }
    cout << endl;
    cout << "Results:\n";
    for (i = 0; i < pupils; ++i)
    {
        cout << ada[i];
        cout << "average: " << ada[i].Average() << endl;
        cout << endl;
    }
    cout << "Done.\n";

    return 0;
}

void set(Student &sa, int n)
{
    cout << "Please enter the student's name: ";
    getline(cin, sa);
    cout << "Please enter " << n << " quiz scores :\n";
    for (int i = 0; i < n; i++)
    {
        cin >> sa[i];
    }
    while (cin.get() != '\n')
    {
        continue;
    }
}
