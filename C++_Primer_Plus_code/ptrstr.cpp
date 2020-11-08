#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    char animal[32] = "bear";
    const char *bird = "wren";
    char *ps;
    cout << animal << " and " << bird << "\n";

    cout << "Enter a kind of animal: ";
    cin.getline(animal, 32);
    ps = animal;
    cout << ps << "\n";
    cout << "Before using strcpy():\n";
    cout << animal << " at " << (int *) animal << endl;
    cout << ps << " at " << (int *) ps << endl;
    ps = new char[strlen(animal) + 1];
    strncpy(ps, animal, strlen(animal) + 1);
    cout << "After using strcpy():\n";
    cout << animal << " at " << (int *) animal << endl;
    cout << ps << " at " << (int *) ps << endl;
    delete[] ps;

    return 0;
}
