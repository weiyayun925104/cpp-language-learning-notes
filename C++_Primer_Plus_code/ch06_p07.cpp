#include <iostream>
#include <cctype>
#include <string>

int main()
{
    std::cout << "Enter words (q to quit): " << std::endl;
    std::string words;

    int vowels = 0;
    int consonants = 0;
    int others = 0;

    while (std::cin >> words && words != "q")
    {
        if (isalpha(words[0]))
        {
            switch (words[0])
            {
            case 'a':
            case 'A':
            case 'e':
            case 'E':
            case 'i':
            case 'I':
            case 'o':
            case 'O':
            case 'u':
            case 'U':
            case 'y':
            case 'Y':
                vowels++;
                break;
            default:
                consonants++;
                break;
            }
        }
        else
        {
            others++;
        }
    }

    std::cout << vowels << " words beginning with vowels.\n";
    std::cout << consonants << " words beginning with consonants.\n";
    std::cout << others << " words beginning with any other character.\n";

    return 0;
}
