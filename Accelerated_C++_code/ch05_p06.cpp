#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <chrono>
#include <algorithm>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::stringstream;
using std::vector;
using std::list;
using std::string;
using std::chrono::steady_clock;
using std::sort;
using std::domain_error;

struct Student_info
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

double grade(const Student_info &s)
{
    return s.grade;
}

bool compare(const Student_info &x, const Student_info &y)
{
    return x.name < y.name;
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

istream &read(istream &is, Student_info &s)
{
    double midterm, final;
    vector<double> homework;

    is >> s.name >> midterm >> final;
    read_hw(is, homework);

    if (is)
    {
        s.grade = grade(midterm, final, homework);
    }

    return is;
}

istream &read(istream &is, vector<Student_info> &v)
{
    const int BUFFSIZE = 128;

    stringstream ss;
    char buff[BUFFSIZE];

    while (is.getline(buff, BUFFSIZE))
    {
        ss << buff;
        Student_info student;
        read(ss, student);
        v.push_back(student);
    }

    return is;
}

istream &read(istream &is, list<Student_info> &l)
{
    const int BUFFSIZE = 128;

    stringstream ss;
    char buff[BUFFSIZE];

    while (is.getline(buff, BUFFSIZE))
    {
        ss << buff;
        Student_info student;
        read(ss, student);
        l.push_back(student);
    }

    return is;
}

bool fgrade(const Student_info &s)
{
    return grade(s) < 60;
}

typedef vector<Student_info> students_t;

students_t extract_fails(students_t &students)
{
    students_t fail;
  students_t::size_type s_size = students.size();
  students_t::size_type counter = 0;

  for (students_t::size_type i = 0; i < s_size; i++)
  {
    if (fgrade(students[i])) 
    {
      fail.push_back(students[i]);
    }
    else
    {
      students[counter++] = students[i];
    }
  }

  students.resize(counter);

    return fail;
}

void test_student_info(string file, students_t &s)
{
    ifstream infile;
    students_t failed;

    infile.open(file);
    steady_clock::time_point begin = std::chrono::steady_clock::now();
    read(infile, s);
    steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Microseconds to read " << file << " into students_t s = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << endl;
    infile.close();
    infile.clear();

    begin = std::chrono::steady_clock::now();
    failed = extract_fails(s);
    end = std::chrono::steady_clock::now();
    cout << "Microseconds to extract failed from " << file << " students_t s = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << endl;
}

void test_student_info(string amount)
{
    string file = "students" + amount + ".txt";

    students_t students;

    test_student_info(file, students);
}

int main()
{
    test_student_info("10");
    test_student_info("100");
    test_student_info("1000");
    test_student_info("10000");

    return 0;
}
