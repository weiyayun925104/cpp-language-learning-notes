#include <iostream>
#include <fstream>

int main()
{
    std::ifstream finput;
    finput.open("ch06_p08.txt");

    if ( ! finput.is_open() )
    {
        std::cout << "Could not open file!" << '\n';
        return 0;
    }
    char word;
    int word_count = 0;

    while (finput.get(word))
    {
        word_count++;
    }

    if (finput.eof())
    {
        std::cout << "End of file reached.\n";
    }
    else if (finput.fail())
    {
        std::cout << "Input Fail.\n";
    }

    if (word_count == 0)
    {
        std::cout << "No data in the file.\n";
    }
    else
    {
        std::cout << "Number of characters in the file: " << word_count << std::endl;
    }

    finput.close();

    return 0;
}
