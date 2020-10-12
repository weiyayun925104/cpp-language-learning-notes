#include <ctime>
#include <iomanip>
#include <iostream>
#include "Foo.h"
#include "Bar.h"

using namespace std;

void logging(StringConvertable &object);

int main()
{
    Foo foo;
    Bar bar;

    cout << "Writing objects with logger...\n";
    logging(foo);
    cout << '\n';
    logging(bar);
    cout << '\n';
}

void logging(StringConvertable &object)
{
    time_t cur_time = time(nullptr);
    struct tm timeInfo;
    localtime_r(&cur_time, &timeInfo);

    cout << put_time(&timeInfo, "%d-%m-%Y %H-%M-%S") << endl;
    cout << object.toString() << endl;
}
