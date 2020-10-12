
#include <iostream>
#include <string>

using namespace std;

int findArrayIndex(string itemToFind, string array[], int arraySize, int currentIndex)
{
    if (currentIndex < 0 || currentIndex >= arraySize)
    {
        return -1;
    }
    if (array[currentIndex] == itemToFind)
    {
        return currentIndex;
    }
    return findArrayIndex(itemToFind, array, arraySize, currentIndex - 1);
}

void printArray(string sortedArray[], int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        cout << "Index " << i << ": " << sortedArray[i] << '\n';
    }
    cout << '\n';
}

int main()
{
    const int arraySize = 10;
    cout << "Creating sorted array of " << arraySize << " elements.\n\n";
    string sortedArray[arraySize];
    sortedArray[0] = "Alpha";
    sortedArray[1] = "Beta";
    sortedArray[2] = "Charlie";
    sortedArray[3] = "Echo";
    sortedArray[4] = "Frank";
    sortedArray[5] = "Mark";
    sortedArray[6] = "Omega";
    sortedArray[7] = "Sally";
    sortedArray[8] = "Tango";
    sortedArray[9] = "Zeta";
    printArray(sortedArray, arraySize);

    const int arrayIndexFind = 6;
    cout << "Finding the index for item " << sortedArray[arrayIndexFind] << " in the sorted array...\n\n";

    int arrayIndex = findArrayIndex(sortedArray[arrayIndexFind], sortedArray, arraySize, arraySize - 1);
    cout << "The index found is " << arrayIndex << " while " << arrayIndexFind << " is the correct answer.\n\n";

    string nonExistingItem = "Slimer";
    cout << "Finding the index for non-existing item " << nonExistingItem << " in the sorted array...\n\n";

    int arrayIndexNonExisting = findArrayIndex(nonExistingItem, sortedArray, arraySize, arraySize - 1);
    cout << "The index found is " << arrayIndexNonExisting << " while " << -1 << " is the correct answer.\n\n";
}
