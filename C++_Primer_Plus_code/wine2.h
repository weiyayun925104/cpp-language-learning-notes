#ifndef WINE2_H_
#define WINE2_H_
#include <string>
#include <valarray>
#include <iostream>


using ArrayInt = std::valarray<int>;
using PairArray = std::pair<ArrayInt, ArrayInt>;

class Wine : private std::string, private PairArray
{
private:
    int years;
public:
    Wine(const char *l, int y, const int yr[], const int bot[]);
    Wine(const char *l, int y);
    ~Wine();

    void Show() const;
    void GetBottles();
    const std::string &Label() const;
    int sum() const;
};

#endif
