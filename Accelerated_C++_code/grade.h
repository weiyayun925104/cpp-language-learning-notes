#ifndef GRADE_H_
#define GRADE_H_

#include <vector>
#include "student_info.h"

double grade(double, double, double);
double grade(double, double, const std::vector<double>&);
double grade(const Student_info&);

#endif
