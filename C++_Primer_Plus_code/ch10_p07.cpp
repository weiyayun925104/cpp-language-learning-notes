#include <iostream>
#include "plorg_class.h"


int main()
{
    Plorg Girl;
    Girl.show_data();

    Plorg Man ("Hann", 300);
    Man.show_data();

    Man.change_ci('-', 125);
    Man.show_data();

    Man.change_ci('+', 200);
    Man.show_data();

    Man.change_ci('|', 200);
    Man.show_data();

    return 0;
}
