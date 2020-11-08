#include <iostream>
#include <cstring>
#include <string>

int main()
{
    char exit_word[8] = "done";
    char word[128];
    int count = 0;

    std::cout << "Type in the words (to complete, enter the word done): " << std::endl;

    do
    {
        if (std::cin >> word)
        {
            std::cout << word << std::endl;
            count++;
        }
        else
        {
            std::cout << "You entered " << count << " words." << std::endl;
            return 0;
        }
    }
    while (strcmp(word, exit_word));

    std::cout << "You entered " << count - 1 << " words." << std::endl;

    return 0;
}
