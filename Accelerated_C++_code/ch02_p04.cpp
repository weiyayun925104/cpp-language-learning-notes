#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;

int FrameDynamicAlt(istream &in, ostream &out, const int pad)
{
    out << "Please enter your first name: ";
    string name;
    in >> name;
    out << endl;

    const string greeting = "Hello, " + name + "!";
    const int rows = pad * 2 + 3;
    const string::size_type cols = greeting.size() + pad * 2 + 2;

    for (int r = 0; r != rows; r++)
    {
        string::size_type c = 0;
        while (c != cols)
        {
            if (r == rows / 2 && c == pad + 1)
            {
                out << greeting;
                c += greeting.size();
            }
            else if (r != 0 && r != rows - 1 && r != rows / 2 && c != 0 && c != cols - 1)
            {
                out << string(cols - 2, ' ');
                c += cols - 2;
            }
            else
            {
                if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1)
                {
                    out << "*";
                }
                else
                {
                    out << " ";
                }
                c++;
            }
        }
        out << std::endl;
    }

    return 0;
}

int main()
{
    int padding;
    cout << "Please enter frame padding: ";
    cin >> padding;
    cout << endl;

    return FrameDynamicAlt(cin, cout, padding);
}
