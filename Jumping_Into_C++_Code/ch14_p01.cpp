
#include <iostream>
#include <string>

using namespace std;

void printBoard(int tableSize, int **table, int maxEntrySize);
string numberWithPadding(int number, int maxSize);
int numberOfPaddingItems(int number, int maxSize);

int main()
{
    int tableSize = 10;

    cout << "Please specify the size of the multiplication table (Default is 10x10): ";
    cin >> tableSize;

    int **p_p_table;
    p_p_table = new int * [tableSize];

    for (int i = 0; i < tableSize; i++)
    {
        p_p_table[i] = new int[tableSize];
    }

    for (int i = 0; i < tableSize; i++)
    {
        for (int j = 0; j < tableSize; j++)
        {
            p_p_table[i][j] = i * j;
        }
    }
    int maxEntrySize = (tableSize - 1) * (tableSize - 1);
    printBoard(tableSize, p_p_table, maxEntrySize);

    for (int i = 0; i < tableSize; i++)
    {
        delete [] p_p_table[i];
    }
    delete [] p_p_table;
}

string numberWithPadding(int number, int maxSize)
{
    string numberAsString = to_string(number);
    string zeros;
    int paddingCount = numberOfPaddingItems(number, maxSize);
    if (paddingCount > 0)
    {
        for (int i = 0; i < paddingCount; i++)
        {
            zeros += '0';
        }
        numberAsString = zeros + numberAsString;
    }
    return numberAsString;
}

int numberOfPaddingItems(int number, int maxSize)
{
    string numberAsString = to_string(number);
    string maxSizeAsString = to_string(maxSize);

    return (maxSizeAsString.length() - numberAsString.length());
}

void printBoard(int tableSize, int **p_p_table, int maxEntrySize)
{
    string horizontalBar = " _";
    for (int i = 0; i < tableSize; i++)
    {
        horizontalBar += "__";
        int paddingCount = numberOfPaddingItems(1, maxEntrySize);
        if (paddingCount > 0)
        {
            for (int j = 0; j < paddingCount; j++)
            {
                horizontalBar += "_";
            }
        }
    }

    for (int i = 0; i <= tableSize; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j <= tableSize; j++)
            {
                if (j == 0)
                {
                    cout << " ";
                }
                else
                {
                    cout << " " << numberWithPadding(j - 1, maxEntrySize);
                }
            }
            cout << "\n";
        }
        else
        {
            cout << horizontalBar << "\n";
            for (int j = 0; j <= tableSize; j++)
            {
                if (j == 0)
                {
                    cout << i - 1;
                }
                else
                {
                    string value = numberWithPadding(p_p_table[i - 1][j - 1], maxEntrySize);
                    cout << "|" << value;
                }
            }
            cout << "|\n";
        }
    }
    cout << horizontalBar << "\n\n";
}
