#include <iostream>
#include <string>

using namespace std;

int main()
{
    int quizscores[10] = { 20, 20, 20, 20, 20, 19, 20, 18, 20, 20 };
    cout << "Doing it right:\n";
    int i;
    for (i = 0; quizscores[i] == 20; i++)
    {
        cout << "quiz " << i << " is a 20\n";
    }

    // for (i = 0; quizscores[i] = 20; i++)

    return 0;
}
