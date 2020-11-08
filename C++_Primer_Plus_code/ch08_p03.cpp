#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>

void uppercase(std::string &text);

int main()
{
    std::cout << "Enter a string (q to quit) : ";
    std::string text;

    while (std::getline(std::cin, text, '\n') && text != "q")
    {
        uppercase(text);
        std::cout << text << std::endl;
        std::cout << "Next string (q to quit) : ";
    }
    std::cout << "Done." << std::endl;

    return 0;
}

void uppercase(std::string &text)
{
    std::transform(text.begin(), text.end(), text.begin(), ::toupper);
}
