#include <iostream>
#include "person_class.h"

int main()
{
    Person one;
    Person two("Smythecraft");
    Person three = Person("Dimwiddy", "Sam");

    one.Show();
    std::cout << std::endl;
    one.FormalShow();

    std::cout << "=================" << std::endl;

    two.Show();
    std::cout << std::endl;
    two.FormalShow();

    std::cout << "=================" << std::endl;

    three.Show();
    std::cout << std::endl;
    three.FormalShow();

    return 0;
}
