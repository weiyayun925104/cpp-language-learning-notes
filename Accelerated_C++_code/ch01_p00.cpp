#include <iostream>
#include <string>

void AskName(std::ostream &outStream, std::istream &inStream)
{
    outStream << "Please enter your first name: ";
    std::string name;
    inStream >> name;
    outStream << "Hello, " + name + "!" << std::endl;
}

void AskNameFramed(std::ostream &outStream, std::istream &inStream)
{
    outStream << "Please enter your first name: ";
    std::string name;
    inStream >> name;

    const std::string greeting = "Hello, " + name + "!";
    const std::string spaces(greeting.size(), ' ');
    const std::string line3 = '*' + greeting + '*';
    const std::string line2 = '*' + spaces + '*';
    const std::string line1(line2.size(), '*');

    outStream << line1 << std::endl << line2 << std::endl << line3
              << std::endl << line2 << std::endl << line1 << std::endl;
}

int main()
{
    AskName(std::cout, std::cin);
    AskNameFramed(std::cout, std::cin);

    return 0;
}