#include <iostream>

void display_time(int hour, int minutes);

int main()
{

    std::cout << "Enter the number of hours: ";
    int hour = 0;
    std::cin >> hour;

    std::cout << "Enter the number of minutes: ";
    int minutes = 0;
    std::cin >> minutes;

    display_time (hour, minutes);

    return 0;
}

void display_time(int hour, int minutes)
{
    std::cout << "Time: " << hour << ":" << minutes << std::endl;
}
