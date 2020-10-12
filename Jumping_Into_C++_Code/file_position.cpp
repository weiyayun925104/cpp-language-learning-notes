#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main ()
{
    fstream file ( "highscores.txt", ios::in | ios::out );
    if ( ! file.is_open() )
    {
        cout << "Could not open file!" << '\n';
        return 0;
    }
    int new_high_score;
    cout << "Enter a new high score: ";
    cin >> new_high_score;

    streampos pre_score_pos = file.tellg();
    int cur_score;
    while ( file >> cur_score )
    {
        if ( cur_score < new_high_score )
        {
            break;
        }
        pre_score_pos = file.tellg();
    }

    if ( ! file.eof() && file.fail()  )
    {
        cout << "Bad score, could not read, exit\n";
        return 0;
    }

    file.clear();

    file.seekg( pre_score_pos );

    vector<int> scores;
    while ( file >> cur_score )
    {
        scores.push_back( cur_score );
    }
    if ( ! file.eof() && file.fail()  )
    {
        cout << "Bad score, could not read, exit\n";
        return 0;
    }

    file.clear();

    file.seekp( pre_score_pos );
    if ( pre_score_pos != 0 )
    {
        file << endl;
    }
    file << new_high_score << endl;
    for ( vector<int>::iterator itr = scores.begin(); itr != scores.end(); ++itr )
    {
        file << *itr << endl;
    }
}
