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
#include <memory>

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
using std::copy;
using std::accumulate;
using std::find;
using std::find_if;
using std::max;
using std::stable_partition;
using std::streamsize;
using std::setprecision;
using std::chrono::steady_clock;
using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;

template <typename T>
class Vec
{
public:
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef size_t size_type;
    typedef T value_type;

    Vec()
    {
        create();
    }
    explicit Vec(size_type n, const T &val = T())
    {
        create(n, val);
    }
    Vec(const Vec<T> &v)
    {
        create(v.begin(), v.end());
    }

    Vec &operator=(const Vec<T> &);
    ~Vec()
    {
        uncreate();
    }
    T &operator[](size_type i)
    {
        return data[i];
    }
    const T &operator[](size_type i) const
    {
        return data[i];
    }

    void push_back(const T &val, bool double_grow = true)
    {
        if (avail == limit)
        {
            grow(double_grow);
        }
        unchecked_append(val);
    }

    size_type size() const
    {
        return avail - data;
    }
    iterator begin()
    {
        return data;
    }
    const_iterator begin() const
    {
        return data;
    }
    iterator end()
    {
        return avail;
    }
    const_iterator end() const
    {
        return avail;
    }

    ostream &print_vec(ostream &);
    void clear()
    {
        destroy();
    };
    iterator erase(iterator it)
    {
        return destroy(it);
    };
    iterator erase(iterator b, iterator e)
    {
        return destroy(b, e);
    };

private:
    iterator data;
    iterator avail;
    iterator limit;

    allocator<T> alloc;

    void create();
    void create(size_type, const T &);
    void create(const_iterator, const_iterator);

    void uncreate();

    void grow(bool);

    void unchecked_append(const T &);

    void destroy();
    iterator destroy(iterator);
    iterator destroy(iterator, iterator);
};

template <typename T>
void Vec<T>::create()
{
    data = avail = limit = nullptr;
}

template <typename T>
void Vec<T>::create(size_type n, const T &val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    uninitialized_fill(data, limit, val);
}

template <typename T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i);
    limit = avail = uninitialized_copy(i, j, data);
}

template <typename T>
void Vec<T>::uncreate()
{
    if (data != nullptr)
    {
        iterator it = avail;
        while (it != data)
        {
            alloc.destroy(--it);
        }
        alloc.deallocate(data, limit - data);
    }
    data = limit = avail = nullptr;
}

template <typename T>
Vec<T> &Vec<T>::operator=(const Vec<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    uncreate();
    create(rhs.begin(), rhs.end());
    return *this;
}

template <typename T>
void Vec<T>::grow(bool double_grow)
{
    size_type new_size;

    if (double_grow)
    {
        new_size = max(2 * (limit - data), ptrdiff_t(1));
    }
    else
    {
        new_size = (limit - data) + 1;
    }

    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data, avail, new_data);
    uncreate();
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <typename T>
void Vec<T>::unchecked_append(const T &val)
{
    alloc.construct(avail++, val);
}

template<typename T>
std::ostream &Vec<T>::print_vec(std::ostream &os)
{
    if (avail - data > 0)
    {
        iterator iter = data;

        os << *iter++;

        while (iter != avail)
        {
            os << ", " << *iter++;
        }

        os << std::endl;
    }
    return os;
}

template <typename T>
void Vec<T>::destroy()
{
    if (data != nullptr)
    {
        iterator it = avail;
        while (it != data)
        {
            alloc.destroy(--it);
        }
    }
    avail = data;
}

template<typename T>
typename Vec<T>::iterator Vec<T>::destroy(iterator pos)
{
    if (data != nullptr && pos != avail)
    {
        alloc.destroy(pos);
        iterator it = pos + 1;

        while (it != avail)
        {
            alloc.construct(pos++, *it++);
            alloc.destroy(pos);
        }
        avail = pos;
    }
    return avail;
}

template<typename T>
typename Vec<T>::iterator Vec<T>::destroy(iterator b, iterator e)
{
    if (data != nullptr && b != avail && b != e)
    {
        iterator it = b;
        while (it != e)
        {
            alloc.destroy(it++);
        }

        while (e != avail)
        {
            alloc.construct(b++, *e);
            alloc.destroy(e++);
        }

        avail = b;
    }
    return avail;
}

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

istream &read_and_grade(istream &is, Vec<Student_info> &students)
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
    for (Vec<Student_info>::size_type i = 0; i != students.size(); i++)
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
    Vec<Student_info> students;
    string file = "students10_ch06.txt";
    ifstream infile;
    infile.open(file);
    read_and_grade(infile, students);
    infile.close();
    infile.clear();

    for (Vec<Student_info>::const_iterator iter = students.begin(); iter != students.end(); ++iter)
    {
        cout << iter->name() << " is valid = " << iter->valid() << endl;
    }

    return 0;
}

istream &read(istream &is, Vec<Student_info> &v)
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

vector<Student_info> extract(Vec<Student_info> &students, bool criteria(const Student_info &))
{
    Vec<Student_info>::iterator iter = stable_partition(students.begin(), students.end(), criteria);
    vector<Student_info> extracted(iter, students.end());
    students.erase(iter, students.end());

    return extracted;
}

void test_student_info(string file)
{
    Student_info::reset_class_info();
    ifstream infile;
    Vec<Student_info> students;
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

string::size_type width(const Vec<string>& v)
{
  string::size_type maxlen = 0;

  for (Vec<string>::size_type i = 0; i != v.size(); ++i)
  {
    maxlen = max(maxlen, v[i].size());
  }

  return maxlen;
}

Vec<string> frame(const Vec<string>& v)
{
  Vec<string> ret;
  string::size_type maxlen = width(v);
  string border(maxlen + 4, '*');

  ret.push_back(border);

  for (Vec<string>::size_type i = 0; i != v.size(); ++i)
  {
    ret.push_back("* " + v[i] + string(maxlen - v[i].size(), ' ') + " *");
  }

  ret.push_back(border);

  return ret;
}

Vec<string> vcat(const Vec<string>& top, const Vec<string>& bottom)
{
  Vec<string> ret = top;

  for (Vec<string>::const_iterator it = bottom.begin(); it != bottom.end(); ++it)
  {
    ret.push_back(*it);
  }

  return ret;
}

Vec<string> hcat(const Vec<string>& left, const Vec<string>& right)
{
  Vec<string> ret;

  string::size_type width1 = width(left) + 1;

  Vec<string>::size_type i = 0, j = 0;

  while (i != left.size() || j != right.size())
  {
    string s;

    if (i != left.size())
    {
      s = left[i++];
    }

    s += string(width1 - s.size(), ' ');

    if (j != right.size())
    {
      s += right[j++];
    }

    ret.push_back(s);
  }

  return ret;
}

int test_frame()
{
  Vec<string> v1;
  v1.push_back("one test");
  v1.push_back("two test");
  v1.push_back("aye caramba");

  Vec<string> v2;
  v2.push_back("one direction");
  v2.push_back("mama mia");
  v2.push_back("mamo testo");
  v2.push_back("lake district mall");

  Vec<string> vert = vcat(frame(v1), frame(v2));

  Vec<string>::const_iterator iter = vert.begin();

  while (iter != vert.end())
  {
    cout << *iter++ << endl;
  }

  Vec<string> horz = hcat(frame(v1), frame(v2));

  iter = horz.begin();

  while (iter != horz.end())
  {
    cout << *iter++ << endl;
  }

  return 0;
}

int test_grow(int appends)
{
  Vec<int> v1;
  Vec<int> v2;

  steady_clock::time_point begin = std::chrono::steady_clock::now();
  for (int i = 0; i < appends; i++)
  {
    v1.push_back(i);
  }
  steady_clock::time_point end = std::chrono::steady_clock::now();
  cout << "Microseconds to add " << appends << " to vector using double memory method = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << endl;


  begin = std::chrono::steady_clock::now();
  for (int i = 0; i < appends; i++)
  {
    v2.push_back(i, false);
  }
  end = std::chrono::steady_clock::now();
  cout << "Microseconds to add " << appends << " to vector without using double memory method = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << endl;

  return 0;
}

int main()
{
    test_read_and_grade();
    test_student_info();
    cout << endl;
    test_frame();
    cout << endl;
    test_grow(1000);

    return 0;
}
