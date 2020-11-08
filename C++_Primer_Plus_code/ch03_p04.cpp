#include <iostream>
#include <cmath>

int main()
{
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);

    const int Day = 24;
    const int Hour = 60;
    const int Minute = 60;

    long long int enter_seconds = 0;
    std::cout << "Enter the number of seconds: ________\b\b\b\b\b\b\b\b";
    std::cin >> enter_seconds;

    int seconds = (enter_seconds % Minute);
    int minutes = (enter_seconds / Minute) % Hour;
    int hours = ( enter_seconds / (Minute * Hour) ) % Day;
    int days = enter_seconds / (Minute * Hour * Day);

    std::cout << enter_seconds << " seconds = " << days << " days, " << hours << " hours, " << minutes << " minutes, ";
    std::cout << seconds << " seconds" << std::endl;

    return 0;
}
