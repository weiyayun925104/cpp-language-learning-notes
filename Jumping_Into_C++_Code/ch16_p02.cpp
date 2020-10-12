
#include <iostream>
#include <string>

using namespace std;

void printArrayItem(string item, int index);
void printArrayItemsReverse(string array[], int index, int arraySize);

int main()
{
    cout << "Creating array...\n\n";
    const int arraySize = 10;
    string array[arraySize];
    array[0] = "Happy";
    array[1] = "Go";
    array[2] = "Lucky";
    array[3] = "Doggy";
    array[4] = "Do";
    array[5] = "Foo";
    array[6] = "Bar";
    array[7] = "Minnie";
    array[8] = "Minie";
    array[9] = "Moe";

    cout << "Printing Array in order:\n";
    for (int i = 0; i < arraySize; i++)
    {
        printArrayItem(array[i], i);
    }
    cout << "\n\n";

    cout << "Printing Array in reverse order:\n";
    printArrayItemsReverse(array, 0, arraySize);
}

void printArrayItemsReverse(string array[], int index, int arraySize)
{
    if (index < 0)
    {
        return;
    }
    if (index < (arraySize - 1))
    {
        printArrayItemsReverse(array, index + 1, arraySize);
    }
    printArrayItem(array[index], index);
}

void printArrayItem(string item, int index)
{
    cout << "Array Item " << index << ": " << item << '\n';
}
