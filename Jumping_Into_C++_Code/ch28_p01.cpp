#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> readBinaryFile(string fileName);
vector<int> readTextFile(string fileName);
int writeBinaryFile(string fileName, const vector<int> &scores);
int writeTextFile(string fileName, const vector<int> &scores);
int insertBinaryFile(string fileName);
void print(const vector<int> &scores);

int main()
{
    string fileName = "highScores";
    cout << "Writing base file " << fileName << '\n';
    vector<int> scores
    {
        1000,
        987,
        864,
        766,
        744,
        500,
        453,
        321,
        201,
        98,
        5
    };
    writeTextFile(fileName, scores);
    writeBinaryFile(fileName, scores);
    print(scores);

    if (insertBinaryFile(fileName) != 0)
    {
        cout << "Error inserting into binary file. Program will exit...\n";
        return 1;
    }

    vector<int> newScores = readBinaryFile(fileName);
    writeTextFile(fileName, newScores);
    print(newScores);
}

vector<int> readBinaryFile(string fileName)
{
    cout << "Opening binary file " << fileName << '\n';
    ifstream aFile(fileName + ".bin", ios::binary);
    if (!aFile.is_open())
    {
        cout << "Could not open file!" << '\n';
        vector<int> scoresEmpty;
        return scoresEmpty;
    }
    else
    {
        cout << "File is opened!\n";
    }

    cout << "Reading file...\n";

    int numberOfScores;
    if( !aFile.read( reinterpret_cast<char *>(&numberOfScores), sizeof(numberOfScores) ) )
    {
        cout << "Error reading from file." << endl;
        vector<int> scoresEmpty;
        return scoresEmpty;
    }

    vector<int> scores(numberOfScores);
    aFile.read( reinterpret_cast<char *>(&scores[0]), numberOfScores * sizeof(int) );

    return scores;
}

vector<int> readTextFile(string fileName)
{
    cout << "Opening text file " << fileName << '\n';
    ifstream fileReader(fileName + ".txt");
    if (!fileReader.is_open())
    {
        cout << "Could not open file!" << '\n';
        vector<int> scoresEmpty;
        return scoresEmpty;
    }
    else
    {
        cout << "File is opened!\n";
    }

    cout << "Reading file...\n";
    vector<int> scores;
    int score;
    while (fileReader >> score)
    {
        scores.push_back(score);
    }

    return scores;
}

int writeBinaryFile(string fileName, const vector<int> &scores)
{
    if (scores.size() <= 0)
    {
        cout << "Vector is empty.\n";
        return 0;
    }
    cout << "Writing file to binary format..." << '\n';
    ofstream aFile(fileName + ".bin", ios::trunc | ios::binary );
    if (!aFile.is_open())
    {
        cout << "Could not open file!" << '\n';
        return 1;
    }

    int numberOfScores = scores.size();
    if ( !aFile.write( reinterpret_cast<char *>(&numberOfScores), sizeof(numberOfScores) ) )
    {
            cout << "Error writing to file." << endl;
            return 1;
    }
    aFile.write( reinterpret_cast<const char *>(&scores[0]), numberOfScores * sizeof(int) );

    return 0;
}

int writeTextFile(string fileName, const vector<int> &scores)
{
    if (scores.size() <= 0)
    {
        cout << "Vector is empty.\n";
        return 0;
    }
    cout << "Writing file to text format..." << '\n';
    ofstream fileWriter(fileName + ".txt", ios::trunc);
    if (!fileWriter.is_open())
    {
        cout << "Could not open file!" << '\n';
        return 1;
    }

    for (vector<int>::const_iterator itr = scores.begin(), end = scores.end(); itr != end; ++itr)
    {
        fileWriter << *itr << '\n';
    }

    return 0;
}

int insertBinaryFile(string fileName)
{
    cout << "Inserting data into binary file..." << '\n';
    fstream aFile(fileName + ".bin", ios::binary | ios::out | ios::in);

    if (!aFile.is_open())
    {
        cout << "Could not open file!" << '\n';
        return 1;
    }

    int newHighScore;
    cout << "Enter a new high score: ";
    cin >> newHighScore;

    int numberOfScores;
    if ( !aFile.read( reinterpret_cast<char *>(&numberOfScores), sizeof(numberOfScores) ) )
    {
        cout << "Error reading from file." << endl;
        return 1;
    }

    streampos preScorePosition = aFile.tellg();
    int currentScore = 0;
    while ( aFile.read( reinterpret_cast<char *>(&currentScore), sizeof(currentScore) ) )
    {
        if (currentScore < newHighScore)
        {
            break;
        }
        preScorePosition = aFile.tellg();
    }

    if ( !aFile.eof() && aFile.fail() )
    {
        cout << "Bad score, could not read, exit.\n";
        return 1;
    }

    aFile.clear();

    aFile.seekg(preScorePosition);

    vector<int> scores;
    while ( aFile.read( reinterpret_cast<char *>(&currentScore), sizeof(currentScore) ) )
    {
        scores.push_back(currentScore);
    }

    if ( !aFile.eof() && aFile.fail() )
    {
        cout << "Bad score, could not read, exit.\n";
        return 1;
    }

    aFile.clear();

    aFile.seekp(preScorePosition);

    aFile.write( reinterpret_cast<char *>(&newHighScore), sizeof(newHighScore) );
    if (scores.size() > 0)
    {
        aFile.write( reinterpret_cast<char *>(&scores[0]), scores.size() * sizeof(int) );
    }

    numberOfScores++;
    aFile.seekp(0, ios_base::beg);
    if ( !aFile.write( reinterpret_cast<char *>(&numberOfScores), sizeof(numberOfScores) ) )
    {
            cout << "Error writing to file." << endl;
            return 1;
    }

    return 0;
}

void print(const vector<int> &scores)
{

    cout << "File contents are: \n";
    for (vector<int>::const_iterator itr = scores.begin(), end = scores.end(); itr != end; ++itr)
    {
        cout << *itr << '\n';
    }
}
