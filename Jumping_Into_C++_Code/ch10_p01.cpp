
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int findSmallestRemainingElement(int array[], int size, int index);
void swap(int array[], int firstIndex, int secondIndex);
void sort(int array[], int size);
void displayArray(int array[], int size);

int main()
{
    int const size = 10;
    int array[size];
    srand(time(nullptr));
    for (size_t i = 0; i < size; i++)
    {
        array[i] = rand() % 100;
    }
    cout << "Original array: ";
    displayArray(array, size);
    cout << '\n';

    sort(array, size);

    cout << "Sorted array: ";
    displayArray(array, size);
    cout << '\n';
}
void sort(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int index = findSmallestRemainingElement(array, size, i);
        swap(array, i, index);
    }
}
int findSmallestRemainingElement(int array[], int size, int index)
{
    int indexOfSmallestValue = index;
    for (size_t i = index + 1; i < size; i++)
    {
        if (array[i] < array[indexOfSmallestValue])
        {
            indexOfSmallestValue = i;
        }
    }
    return indexOfSmallestValue;
}
void swap(int array[], int firstIndex, int secondIndex)
{
    if (firstIndex == secondIndex)
    {
        return;
    }
    int temp = array[firstIndex];
    array[firstIndex] = array[secondIndex];
    array[secondIndex] = temp;
}
void displayArray(int array[], int size)
{
    cout << "{";
    for (int i = 0; i < size; i++)
    {
        if (i != 0)
        {
            cout << ", ";
        }
        cout << array[i];
    }
    cout << "}";
}
