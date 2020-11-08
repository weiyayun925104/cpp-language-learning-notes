#include <iostream>
#include <cmath>

int main()
{
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);

    const double degree_minute = 60;
    const double degree_second = degree_minute * 60;

    std::cout << "Enter a latitude in degrees, minutes, and seconds: " << std::endl;

    std::cout << "First, enter the degrees:__\b\b ";
    int degrees = 0;
    std::cin >> degrees;

    std::cout << "Next, enter the minutes of arc:__\b\b ";
    int minutes = 0;
    std::cin >> minutes;

    std::cout << "Finally, enter the seconds of arc:__\b\b ";
    int seconds = 0;
    std::cin >> seconds;

    double Result = degrees + (minutes / degree_minute) + (seconds / degree_second);
    std::cout << degrees << " degrees, " << minutes << " minutes, " << seconds << " seconds = " << Result << " degrees\n";

    return 0;
}
