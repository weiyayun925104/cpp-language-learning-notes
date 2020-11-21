#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <numeric>
#include <iomanip>
#include <chrono>

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
using std::list;
using std::map;
using std::string;
using std::getline;
using std::domain_error;
using std::transform;
using std::back_inserter;
using std::sort;
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

    static int default_constructor_calls;
    static int stream_constructor_calls;
    static int copy_constructor_calls;
    static int assignment_calls;
    static int destructor_calls;

public:
    Student_info();
    Student_info(istream &);
    Student_info(const Student_info &);

    Student_info &operator=(const Student_info &);
    ~Student_info();

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

    static void reset_class_info();
    static ostream &print_class_info(ostream &);
};

int Student_info::default_constructor_calls = 0;
int Student_info::stream_constructor_calls = 0;
int Student_info::copy_constructor_calls = 0;
int Student_info::assignment_calls = 0;
int Student_info::destructor_calls = 0;

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

Student_info::Student_info() : midterm(0), final(0)
{
    ++default_constructor_calls;
}

Student_info::Student_info(istream &is)
{
    ++stream_constructor_calls;
    read(is);
}

Student_info::Student_info(const Student_info &student)
{
    ++copy_constructor_calls;

    _name = student._name;
    midterm = student.midterm;
    final = student.final;
    homework = student.homework;
}

Student_info &Student_info::operator=(const Student_info &student)
{
    ++assignment_calls;

    if (this == &student)
    {
        return *this;
    }
    _name = student._name;
    midterm = student.midterm;
    final = student.final;
    homework = student.homework;

    return *this;
}

Student_info::~Student_info()
{
    ++destructor_calls;
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

void Student_info::reset_class_info()
{
    default_constructor_calls = 0;
    stream_constructor_calls = 0;
    copy_constructor_calls = 0;
    assignment_calls = 0;
    destructor_calls = 0;
}

ostream &Student_info::print_class_info(ostream &os)
{
    os << default_constructor_calls << '\t' << "default constructor calls" << endl;
    os << stream_constructor_calls << '\t' << "stream constructor calls" << endl;
    os << copy_constructor_calls << '\t' << "copy constructor calls" << endl;
    os << assignment_calls << '\t' << "assignment calls" << endl;
    os << destructor_calls << '\t' << "destructor calls" << endl;

    return os;
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
            cout << setprecision(3) << final_grade << setprecision(prec) << endl;
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

    for (vector<Student_info>::const_iterator iter = students.begin(); iter != students.end(); ++iter)
    {
        cout << iter->name() << " is valid = " << iter->valid() << endl;
    }

    return 0;
}

istream &read(istream &is, vector<Student_info> &v)
{
    const int BUFFSIZE = 128;

    stringstream ss;
    char buff[BUFFSIZE];

    while (is.getline(buff, BUFFSIZE))
    {
        ss << buff;
        Student_info student(ss);
        v.push_back(student);
    }

    return is;
}

bool fgrade(const Student_info &student)
{
    return student.grade() < 60;
}

bool pgrade(const Student_info &student)
{
    return !fgrade(student);
}

vector<Student_info> extract(vector<Student_info> &students, bool criteria(const Student_info &))
{
    vector<Student_info>::iterator iter = stable_partition(students.begin(), students.end(), criteria);
    vector<Student_info> extracted(iter, students.end());
    students.erase(iter, students.end());

    return extracted;
}

void test_student_info(string file)
{
    Student_info::reset_class_info();
    ifstream infile;
    vector<Student_info> students;
    vector<Student_info> failed;

    infile.open(file);
    steady_clock::time_point begin = std::chrono::steady_clock::now();
    read(infile, students);
    steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Microseconds to read " << file << " into vector = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << endl;
    Student_info::print_class_info(cout);
    infile.close();
    infile.clear();
    Student_info::reset_class_info();

    begin = std::chrono::steady_clock::now();
    failed = extract(students, pgrade);
    end = std::chrono::steady_clock::now();
    cout << "Microseconds to extract failed from " << file << " student vector = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << endl;
    Student_info::print_class_info(cout);
}

void test_student_info()
{
    test_student_info("students10.txt");
    cout << endl;
    test_student_info("students100.txt");
    cout << endl;
    test_student_info("students1000.txt");
    cout << endl;
    test_student_info("students10000.txt");
}

int main()
{
    test_read_and_grade();
    test_student_info();

    return 0;
}
