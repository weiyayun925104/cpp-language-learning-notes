#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <numeric>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ifstream;
using std::ostream;
using std::stringstream;
using std::vector;
using std::string;
using std::domain_error;
using std::transform;
using std::back_inserter;
using std::remove_if;
using std::remove_copy_if;
using std::remove_copy;
using std::stable_partition;
using std::sort;
using std::accumulate;
using std::find;

struct Student_info
{
    std::string name;
    std::vector<double> homework;
    double midterm;
    double final;
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

double average(const vector<double> &v)
{
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
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
    return grade(s.midterm, s.final, s.homework);
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
    is >> s.name >> s.midterm >> s.final;
    read_hw(is, s.homework);

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

bool did_all_hw(const Student_info &s)
{
    return ( find(s.homework.begin(), s.homework.end(), 0) == s.homework.end() );
}

bool fgrade(const Student_info &s)
{
    return grade(s) < 60;
}

bool pgrade(const Student_info &s)
{
    return !fgrade(s);
}

double grade_aux(const Student_info &s)
{
    try
    {
        return grade(s);
    }
    catch (domain_error)
    {
        return grade(s.midterm, s.final, 0);
    }
}

double median_analysis(const vector<Student_info> &students)
{
    vector<double> grades;
    transform(students.begin(), students.end(), back_inserter(grades), grade_aux);
    return median(grades);
}

double average_grade(const Student_info &s)
{
    return grade(s.midterm, s.final, average(s.homework));
}

double average_analysis(const vector<Student_info> &students)
{
    vector<double> grades;
    transform(students.begin(), students.end(), back_inserter(grades), average_grade);
    return median(grades);
}

double optimistic_median(const Student_info &s)
{
    vector<double> nonzero;

    remove_copy(s.homework.begin(), s.homework.end(), back_inserter(nonzero), 0);

    if (nonzero.empty())
    {
        return grade(s.midterm, s.final, 0);
    }
    else
    {
        return grade(s.midterm, s.final, median(nonzero));
    }
}

double optimistic_median_analysis(const vector<Student_info> &students)
{
    vector<double> grades;
    transform(students.begin(), students.end(), back_inserter(grades), optimistic_median);
    return median(grades);
}

double analysis(const vector<Student_info> &students, double method(const Student_info &))
{
    vector<double> grades;
    transform(students.begin(), students.end(), back_inserter(grades), method);
    return median(grades);
}

void write_analysis(ostream &out, const string &name, double method(const Student_info &),
                    const vector<Student_info> &did, const vector<Student_info> &didnt)
{
    out << name << ": median(did) = " << analysis(did, method) << ", median(didnt) = " << analysis(didnt, method) << endl;
}

void write_analysis(ostream &out, const string &name, double method(const vector<Student_info> &),
                    const vector<Student_info> &did, const vector<Student_info> &didnt)
{
    out << name << ": median(did) = " << method(did) << ", median(didnt) = " << method(didnt) << endl;
}

vector<Student_info> extract_fails(vector<Student_info> &students)
{
    vector<Student_info> fail;
    remove_copy_if(students.begin(), students.end(), back_inserter(fail), pgrade);
    students.erase(remove_if(students.begin(), students.end(), fgrade), students.end());

    return fail;
}

vector<Student_info> extract_not_all_hw(vector<Student_info>& students) 
{
  vector<Student_info>::iterator iter = stable_partition(students.begin(), students.end(), did_all_hw);
  vector<Student_info> not_all_hw(iter, students.end());
  students.erase(iter, students.end());

  return not_all_hw;
}

vector<Student_info> extract(vector<Student_info>& students, bool criteria(const Student_info&)) 
{
  vector<Student_info>::iterator iter = stable_partition(students.begin(), students.end(), criteria);
  vector<Student_info> extracted(iter, students.end());
  students.erase(iter, students.end());

  return extracted;
}

int main()
{
    vector<Student_info> all;
    Student_info student;

    string file = "students10_ch06.txt";
    ifstream infile;
    infile.open(file);
    read(infile, all);
    infile.close();
    infile.clear();

    for (vector<Student_info>::const_iterator iter = all.begin(); iter != all.end(); iter++)
    {
        if (did_all_hw(*iter))
        {
            cout << "did ";
        }
        else
        {
            cout << "didnt ";
        }
        cout << iter->name << ": " << iter->midterm << ", " << iter->final << ", " << iter->homework.size() << endl;
    }
    cout << endl;
    vector<Student_info> did (all);
    vector<Student_info> didnt = extract(did, did_all_hw);

    if (did.empty())
    {
        cout << "No student did all the homework!" << endl;
        return 1;
    }

    if (didnt.empty())
    {
        cout << "Every student did all the homework!" << endl;
        return 1;
    }

    write_analysis(cout, "median", median_analysis, did, didnt);
    write_analysis(cout, "average", average_analysis, did, didnt);
    write_analysis(cout, "optimistic median", optimistic_median_analysis, did, didnt);
    write_analysis(cout, "median", grade_aux, did, didnt);
    write_analysis(cout, "average", average_grade, did, didnt);
    write_analysis(cout, "optimistic median", optimistic_median, did, didnt);

    vector<Student_info> failed = extract(all, pgrade);
    for (vector<Student_info>::const_iterator iter = all.begin(); iter != all.end(); iter++)
    {
        cout << iter->name << ": " << iter->midterm << ", " << iter->final << ", " << iter->homework.size() << endl;
    }
    cout << endl;

    for (vector<Student_info>::const_iterator iter = failed.begin(); iter != failed.end(); iter++)
    {
        cout << iter->name << ": " << iter->midterm << ", " << iter->final << ", " << iter->homework.size() << endl;
    }
    cout << endl;

    return 0;
}
