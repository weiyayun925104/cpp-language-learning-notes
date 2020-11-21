#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <numeric>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <cstring>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::map;
using std::string;
using std::getline;
using std::domain_error;
using std::transform;
using std::back_inserter;
using std::sort;
using std::copy;
using std::accumulate;
using std::find;
using std::max;
using std::streamsize;
using std::setprecision;
using std::chrono::steady_clock;

class Student_info
{
private:
    string _name;
    double midterm, final;
    vector<double> homework;

public:
    Student_info();
    Student_info(istream &);

    istream &read(istream &);
    double grade() const;
    const string &name() const
    {
        return _name;
    }
    bool valid() const
    {
        return !homework.empty();
    }
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

double grade(double midterm, double final, const vector<double> &hw)
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
    }

    return is;
}

Student_info::Student_info() : midterm(0), final(0) { }

Student_info::Student_info(istream &is)
{
    read(is);
}

istream &Student_info::read(istream &in)
{
    in >> _name >> midterm >> final;
    read_hw(in, homework);
    return in;
}

double Student_info::grade() const
{
    return ::grade(midterm, final, homework);
}

string letter_grade(double grade)
{
    static const double numbers[] =
    {
        97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
    };
    static const char *const letters[] =
    {
        "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
    };
    static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);
    for (size_t i = 0; i < ngrades; ++i)
    {
        if (grade >= numbers[i])
        {
            return letters[i];
        }
    }
    return "?\?\?";
}

bool compare(const Student_info &x, const Student_info &y)
{
    return x.name() < y.name();
}

istream &read_and_grade(istream &is, vector<Student_info> &students)
{
    const int BUFFSIZE = 128;

    stringstream ss;
    char buff[BUFFSIZE];
    string::size_type maxlen = 0;

    while (is.getline(buff, BUFFSIZE))
    {
        ss << buff;
        Student_info student(ss);
        maxlen = max(maxlen, student.name().size());
        students.push_back(student);
    }
    sort(students.begin(), students.end(), compare);
    for (vector<Student_info>::size_type i = 0; i != students.size(); i++)
    {
        cout << students[i].name() << string(maxlen + 1 - students[i].name().size(), ' ');

        try
        {
            double final_grade = students[i].grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade << setprecision(prec) << " ";
            cout << letter_grade(final_grade) << endl;
        }
        catch (domain_error e)
        {
            cout << e.what() << endl;
        }
    }

    return is;
}


int test_read_and_grade()
{
    vector<Student_info> students;
    string file = "students10_ch06.txt";
    ifstream infile;
    infile.open(file);
    read_and_grade(infile, students);
    infile.close();
    infile.clear();

    return 0;
}

int main()
{
    test_read_and_grade();
    return 0;
}

