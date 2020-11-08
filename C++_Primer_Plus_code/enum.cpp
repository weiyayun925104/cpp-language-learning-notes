#include <iostream>

using namespace std;

enum { red, orange, yellow, green, blue, violet, indigo };

int main()
{

    cout << "Enter color code (0-6): ";
    int code = 0;
    cin >> code;
    while (code >= red && code <= indigo)
    {
        switch (code)
        {
        case red:
            cout << "Her lips were red.\n";
            break;
        case orange:
            cout << "Her hair was orange.\n";
            break;
        case yellow:
            cout << "Her shoes were yellow.\n";
            break;
        case green:
            cout << "Her nails were green.\n";
            break;
        case blue:
            cout << "Her sweatsuit was blue.\n";
            break;
        case violet:
            cout << "Her eyes were violet.\n";
            break;
        case indigo:
            cout << "Her mood was indigo.\n";
            break;
        default :
            cout << "code invalid\n";
            break;
        }
        cout << "Enter color code (0-6): ";
        code = 0;
        cin >> code;
    }
    cout << "Done.\n";

    return 0;
}
