#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

using std::istream;
using std::streamsize;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::max;
using std::sort;
using std::setprecision;
using std::domain_error;

struct Student_info_extra
{
    std::string name;
    double grade;
};

double median(vector<double> vec)
{
    typedef vector<double>::size_type vec_sz;

    vec_sz size = vec.size();
    if (size == 0)
    {
        throw domain_error("median of empty vector");
    }

    sort(vec.begin(), vec.end());
    vec_sz mid = size / 2;

    return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const std::vector<double> &hw)
{
    if (hw.size() == 0)
    {
        throw domain_error("Student has done no homework");
    }
    return grade(midterm, final, median(hw));
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

bool compare_students(const Student_info_extra &x, const Student_info_extra &y)
{
    return x.name < y.name;
}

istream &read(istream &is, Student_info_extra &s)
{
    double midterm, final;
    vector<double> homework;
    cout << "Please enter your name: ";
    std::getline(is, s.name, '\n');
    if (is && s.name != "")
    {
        cout << "Please enter your midterm and final exam grades: ";
        is >> midterm >> final;
        cout << "Enter all your homework grades: ";
        read_hw(is, homework);
        s.grade = grade(midterm, final, homework);

    }

    return is;
}

int main()
{
    vector<Student_info_extra> students;
    Student_info_extra record;
    string::size_type maxlen = 0;

    cout << std::fixed << std::left;

    try
    {
        while (read(cin, record) && record.name != "")
        {
            maxlen = max(maxlen, record.name.size());
            students.push_back(record);
        }
    }
    catch (domain_error e)
    {
        cout << e.what() << endl;
    }

    sort(students.begin(), students.end(), compare_students);

    for (vector<Student_info_extra>::size_type i = 0; i != students.size(); i++)
    {
        cout << std::setw(maxlen + 1) << students[i].name;
        streamsize prec = cout.precision();
        cout << setprecision(3) << students[i].grade << setprecision(prec);

        cout << endl;
    }

    return 0;
}
