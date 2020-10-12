
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

bool isSorted(int array[], int size);
bool isAscending(int array[], int size);
int findSmallestRemainingElement(int array[], int size, int index);
int findLargestRemainingElement(int array[], int size, int index);
void swap(int array[], int firstIndex, int secondIndex);
void sort(int array[], int size, bool ascending);
void displayArray(int array[], int size);


int main()
{
    int const size = 10;
    int array[size];
    srand(time(nullptr));
    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % 100;
    }
    cout << "Original array: ";
    displayArray(array, size);
    cout << '\n';

    if (isSorted(array, size))
    {
        cout << "Array is sorted. No sorting action will be done." << '\n';
    }
    else
    {
        cout << "Array is not sorted. " << '\n';
        cout << "Array will be sorted based on the ordering of the first two elements." << '\n';
        bool isArrayAscending = isAscending(array, size);

        sort(array, size, isArrayAscending);

        cout << "Sorted array: ";
        displayArray(array, size);
        cout << '\n';

        if (isSorted(array, size))
        {
            cout << "Array has been correctly sorted." << '\n';
        }
    }
}

bool isAscending(int array[], int size)
{
    if (size >= 2)
    {
        return (array[1] >= array[0]);
    }
    return false;
}

bool isSorted(int array[], int size)
{
    bool isArrayAscending = isAscending(array, size);

    for (int i = 1; i < size; i++)
    {
        if ( isArrayAscending && (array[i] < array[i - 1]) )
        {
            return false;
        }

        if ( !isArrayAscending && (array[i] > array[i - 1]) )
        {
            return false;
        }
    }
    return true;
}

void sort(int array[], int size, bool ascending)
{
    for (int i = 0; i < size; i++)
    {
        int index;
        if (ascending)
        {
            index = findSmallestRemainingElement(array, size, i);
        }
        else
        {
            index = findLargestRemainingElement(array, size, i);
        }
        swap(array, i, index);
    }
}


int findSmallestRemainingElement(int array[], int size, int index)
{
    int indexOfSmallestValue = index;
    for (int i = index + 1; i < size; i++)
    {
        if (array[i] < array[indexOfSmallestValue])
        {
            indexOfSmallestValue = i;
        }
    }
    return indexOfSmallestValue;
}

int findLargestRemainingElement(int array[], int size, int index)
{
    int indexOfLargestValue = index;
    for (int i = index + 1; i < size; i++)
    {
        if (array[i] > array[indexOfLargestValue])
        {
            indexOfLargestValue = i;
        }
    }
    return indexOfLargestValue;
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
    for (size_t i = 0; i < size; i++)
    {
        if (i != 0)
        {
            cout << ", ";
        }
        cout << array[i];
    }
    cout << "}";
}
