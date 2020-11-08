#include <iostream>
#include <string>

int main()
{
    std::string month[12] =
    {
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };

    int total_book = 0;
    int array_book_sold[12];

    for (int i = 0; i < 12; i++)
    {
        std::cout << "Enter the number of books sold for: " << month[i] << std::endl;
        std::cin >> array_book_sold[i];

        total_book += array_book_sold[i];
    }
    std::cout << "Total books sold: " << total_book << std::endl;

    return 0;
}
