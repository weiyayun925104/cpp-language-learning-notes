#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <exception>
#include <stdexcept>

using std::cin;
using std::cout;
using std::streamsize;
using std::endl;
using std::vector;
using std::string;
using std::setprecision;
using std::sort;
using std::max;
using std::domain_error;

#include "student_info.h"
#include "grade.h"

int main()
{
  vector<Student_info> students;
  Student_info record;
  string::size_type maxlen = 0;

  cout << std::fixed << std::left;

  while (read(cin, record) && record.name != "")
  {
    maxlen = max(maxlen, record.name.size());
    students.push_back(record);
    record.homework.clear();
  }

  sort(students.begin(), students.end(), compare);

  for (vector<Student_info>::size_type i = 0; i != students.size(); i++) 
  {
    cout << std::setw(maxlen+1) << students[i].name;

    try 
    {
      double final_grade = grade(students[i]);
      streamsize prec = cout.precision();
      cout << setprecision(3) << final_grade << setprecision(prec);
    }
    catch (domain_error & e) 
    {
      cout << e.what();
    }
    cout << endl;
  }

  return 0;
}
