#include <iostream>
#include <string>

bool isPalindrome(std::string &str);

int main()
{
    std::cout << "Enter a string: ";
    std::string str;
    std::getline(std::cin, str, '\n');

    if (isPalindrome(str))
    {
        std::cout << str << " is a palindrome" << std::endl;
    }
    else
    {
        std::cout << str << " is not a palindrome" << std::endl;
    }

    return 0;
}

bool isPalindrome(std::string &str)
{
    for (int i = 0, j = str.size() - 1; i < j; i++, j--)
    {
        if (str[i] != str[j])
        {
            return false;
        }
    }
    return true;
}
