#include <iostream>
#include <string>

using namespace std;

int arrayMaxLength = 8;

struct Talk
{
    string name;
    string daysSinceLastSpoken;
};

void updateArray(Talk *p_array, int size, string name, int daySinceLastSpoken);
Talk *addToArray(Talk *p_array, int *size, string name, int daySinceLastSpoken);
void disposeArray(Talk *p_array);
Talk *arraySortedByName(Talk *p_array, int size);
Talk *arraySortedByDate(Talk *p_array, int size);
bool nameExistsInArray(Talk *p_array, int size, string name);
string getName();
int getDaysSinceLastSpoken();
int getDaysSinceLastSpoken(int lastDaysSinceLastSpoken);
int lookUpDaysSinceLastSpoken(Talk *p_array, int size, string name);

string getNameToUpdate(Talk *p_array, int size);
void printFriends(Talk *p_array, int size);
void printFriendsByName(Talk *p_array, int size);
void printFriendsByDate(Talk *p_array, int size);

int findSmallestElementByName(Talk *p_array, int size, int index);
int findSmallestElementByDate(Talk *p_array, int size, int index);
void swap(Talk *p_array, int firstIndex, int secondIndex);
void sortByName(Talk *p_array, int size);
void sortByDate(Talk *p_array, int size);

int main()
{
    int arrayLength = 0;
    Talk *p_array = new Talk[ arrayMaxLength ];

    int option = 0;
    string name;
    int daysSinceLastSpoken;
    do
    {
        cout << "Please select an option:\n";
        cout << "(1) Add new friend\n";
        if(arrayLength > 0)
        {
            cout << "(2) Update friend\n";
            cout << "(3) List friends by name\n";
            cout << "(4) List friends by most recently spoken with\n";
        }
        cout << "(0) Exit\n";
        cin >> option;
        cin.clear();
        cin.ignore(80, '\n');

        cout << '\n';
        switch (option)
        {
        case 1:
            name = getName();
            daysSinceLastSpoken = getDaysSinceLastSpoken();
            p_array = addToArray(p_array, &arrayLength, name, daysSinceLastSpoken);
            cout << '\n';
            break;
        case 2:
            name = getNameToUpdate(p_array, arrayLength);
            daysSinceLastSpoken = lookUpDaysSinceLastSpoken(p_array, arrayLength, name);
            daysSinceLastSpoken = getDaysSinceLastSpoken(daysSinceLastSpoken);
            updateArray(p_array, arrayLength, name, daysSinceLastSpoken);
            cout << '\n';
            break;
        case 3:
            printFriendsByName(p_array, arrayLength);
            cout << '\n';
            break;
        case 4:
            printFriendsByDate(p_array, arrayLength);
            cout << '\n';
            break;
        case 0:
            break;
        default:
            break;
        }
    }
    while (option != 0);

    disposeArray(p_array);
}
string getName()
{
    string name;
    cout << "Friend name: ";
    getline(cin, name, '\n');
    cout << '\n';
    return name;
}
int getDaysSinceLastSpoken()
{
    int daysSinceLastSpokenInput = 0;
    do
    {
        cout << "Number of days ago you last spoke with them: ";
        cin >> daysSinceLastSpokenInput;
        cin.clear();
        cin.ignore(80, '\n');

        if (daysSinceLastSpokenInput < 0)
        {
            cout << "Please enter a value >= 0\n";
        }
    }
    while (daysSinceLastSpokenInput < 0);
    cout << '\n';
    return daysSinceLastSpokenInput;
}
int getDaysSinceLastSpoken(int lastDaysSinceLastSpoken)
{
    int daysSinceLastSpokenInput = 0;
    do
    {
        cout << "Number of days ago you last spoke with them: ";
        cin >> daysSinceLastSpokenInput;
        cin.clear();
        cin.ignore(80, '\n');

        if (daysSinceLastSpokenInput < 0)
        {
            cout << "Please enter a value >= 0\n\n";
        }
        if (daysSinceLastSpokenInput > lastDaysSinceLastSpoken)
        {
            cout << "You last spoke with your friend " << lastDaysSinceLastSpoken << " days ago.\n";
            cout << "You must enter a number less than or equal to this.\n\n";
        }
    }
    while ((daysSinceLastSpokenInput < 0) || (daysSinceLastSpokenInput > lastDaysSinceLastSpoken));
    cout << '\n';
    return daysSinceLastSpokenInput;
}
int lookUpDaysSinceLastSpoken(Talk *p_array, int size, string name)
{
    for (int i = 0; i < size; i++)
    {
        if (p_array[i].name == name)
        {
            return stoi( p_array[i].daysSinceLastSpoken );
        }
    }
    return -1;
}
string getNameToUpdate(Talk *p_array, int size)
{
    string name;
    do
    {
        printFriendsByName(p_array, size);
        cout << '\n';
        cout << "Please enter an existing name to update: ";
        getline(cin, name, '\n');
        cout << '\n';
    }
    while (!nameExistsInArray(p_array, size, name));
    return name;
}
bool nameExistsInArray(Talk *p_array, int size, string name)
{
    for (int i = 0; i < size; i++)
    {
        if (p_array[i].name == name)
        {
            return true;
        }
    }
    return false;
}
void updateArray(Talk *p_array, int size, string name, int daySinceLastSpoken)
{
    for (int i = 0; i < size; i++)
    {
        if (p_array[i].name == name)
        {
            p_array[i].daysSinceLastSpoken = to_string(daySinceLastSpoken);
            return;
        }
    }
}
Talk *addToArray(Talk *p_array, int *size, string name, int daySinceLastSpoken)
{
    if (*size >= arrayMaxLength)
    {
        Talk *p_newvalues = new Talk[ arrayMaxLength * 2 ];
        for (int j = 0; j < arrayMaxLength; j++)
        {
            p_newvalues[j] = p_array[j];
        }
        p_newvalues[arrayMaxLength].name = name;
        p_newvalues[arrayMaxLength].daysSinceLastSpoken = to_string(daySinceLastSpoken);
        disposeArray(p_array);
        *size += 1;
        arrayMaxLength *= 2;
        return p_newvalues;
    }
    else
    {
        p_array[*size].name = name;
        p_array[*size].daysSinceLastSpoken = to_string(daySinceLastSpoken);
        *size += 1;
        return p_array;
    }
}
void disposeArray(Talk *p_array)
{
    delete[] p_array;
}
Talk *arraySortedByName(Talk *p_array, int size)
{
    Talk *p_newArray = new Talk[size];
    for (int i = 0; i < size; i++)
    {
        p_newArray[i] = p_array[i];
    }
    sortByName(p_newArray, size);

    return p_newArray;
}

Talk *arraySortedByDate(Talk *p_array, int size)
{
    Talk *p_newArray = new Talk[size];
    for (int i = 0; i < size; i++)
    {
        p_newArray[i] = p_array[i];
    }
    sortByDate(p_newArray, size);

    return p_newArray;
}
void printFriendsByName(Talk *p_array, int size)
{
    Talk *sortedArray = arraySortedByName(p_array, size);
    printFriends(sortedArray, size);
    disposeArray(sortedArray);
}
void printFriendsByDate(Talk *p_array, int size)
{
    Talk *sortedArray = arraySortedByDate(p_array, size);
    printFriends(sortedArray, size);
    disposeArray(sortedArray);
}
void printFriends(Talk *p_array, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << p_array[i].name << ": " << p_array[i].daysSinceLastSpoken << " days since last spoken\n";
    }
}
void sortByName(Talk *p_array, int size)
{
    for (int i = 0; i < size; i++)
    {
        int index = findSmallestElementByName(p_array, size, i);
        swap(p_array, i, index);
    }
}
void sortByDate(Talk *p_array, int size)
{
    for (int i = 0; i < size; i++)
    {
        int index = findSmallestElementByDate(p_array, size, i);
        swap(p_array, i, index);
    }
}
int findSmallestElementByName(Talk *p_array, int size, int index)
{
    int indexOfSmallestValue = index;
    for (int i = index + 1; i < size; i++)
    {
            if ( p_array[i].name < p_array[indexOfSmallestValue].name )
            {
                indexOfSmallestValue = i;
            }
    }
    return indexOfSmallestValue;
}
int findSmallestElementByDate(Talk *p_array, int size, int index)
{
    int indexOfSmallestValue = index;
    for (int i = index + 1; i < size; i++)
    {
            int arrayCurrent = stoi( p_array[i].daysSinceLastSpoken );
            int arraySmallest = stoi( p_array[indexOfSmallestValue].daysSinceLastSpoken );
            if (arrayCurrent < arraySmallest)
            {
                indexOfSmallestValue = i;
            }
    }
    return indexOfSmallestValue;
}
void swap(Talk *p_array, int firstIndex, int secondIndex)
{
    if (firstIndex == secondIndex)
    {
        return;
    }
    Talk temp = p_array[firstIndex];
    p_array[firstIndex] = p_array[secondIndex];
    p_array[secondIndex] = temp;
}
