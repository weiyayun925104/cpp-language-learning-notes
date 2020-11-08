#include <iostream>
#include <string>

const int ArSize = 128;

void strcount(const std::string str);

int main()
{
    std::string input;
    std::string next;

    std::cout << "Enter a line: ";
    while ( std::getline(std::cin, input, '\n') && input != "")
    {
        strcount(input);
        std::cout << "Enter a line : ";
    }

    std::cout << "Done." << std::endl;

    return 0;
}

void strcount(const std::string str)
{
    static int total = 0;
    int count = 0;

    std::cout << "\"" << str << "\" contains ";

    for (int i = 0; i < str.size(); i++)
    {
        count++;
    }

    total += count;
    std::cout << count << " characters\n";
    std::cout << total << " characters total\n";
}
