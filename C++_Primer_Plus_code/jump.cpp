#include <iostream>

using namespace std;

const int ArSize = 128;

int main()
{
    char line[ArSize] = {0};
    int spaces = 0;

    cout << "Enter a line of text:\n";
    cin.get(line, ArSize);
    cin.get();
    cout << "Complete line:\n" << line << endl;
    cout << "Line through first period:\n";
    for (int i = 0; line[i] != '\0'; i++)
    {
        cout << line[i];
        if (line[i] == '.')
        {
            break;
        }
        if (line[i] != ' ')
        {
            continue;
        }
        spaces++;
    }
    cout << "\n" << spaces << " spaces\n";
    cout << "Done.\n";

    return 0;
}
