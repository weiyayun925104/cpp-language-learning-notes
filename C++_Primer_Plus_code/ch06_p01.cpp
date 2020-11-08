#include <iostream>
#include <cctype>

int main()
{
    std::cout << "Type the text (@ means the end)" << std::endl;
    char ch;
    std::cin.get(ch);

    while (ch != '@')
    {
        if (isalpha(ch))
        {
            if (islower(ch))
            {
                std::cout << char(toupper(ch));
            }
            else
            {
                std::cout << char(tolower(ch));
            }
        }
        else
        {
            std::cout << ch;
        }
        std::cin.get(ch);
    }
    std::cout << std::endl;

    return 0;
}
