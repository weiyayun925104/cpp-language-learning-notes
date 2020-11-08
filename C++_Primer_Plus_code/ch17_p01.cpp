#include <iostream>

int main()
{
    std::cout << "Please enter string: ";

    char ch;
    std::cin.get(ch);

    int count = 0;
    while (ch != '$')
    {
        count++;
        std::cin.get(ch);
    }
    std::cin.putback(ch);

    std::cout << "count = " << count << std::endl;
    std::cout << "The next character in the input buffer is ";
    std::cout << (char) std::cin.get() << std::endl;

    return 0;
}
