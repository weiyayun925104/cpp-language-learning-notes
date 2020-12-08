#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <numeric>
#include <iomanip>
#include <chrono>
#include <memory>
#include <cstring>
#include <cmath>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::list;
using std::map;
using std::string;
using std::getline;
using std::to_string;
using std::domain_error;
using std::runtime_error;
using std::transform;
using std::back_inserter;
using std::ostream_iterator;
using std::sort;
using std::copy;
using std::accumulate;
using std::find;
using std::find_if;
using std::max;
using std::min;
using std::stable_partition;
using std::streamsize;
using std::setprecision;
using std::chrono::steady_clock;
using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

int main()
{
    cout << "How many different moves (at least one) should the computer have?\n";
    int num_moves = 0;
    cin >> num_moves;
    if (num_moves < 1)
    {
        error("Number of moves must be at least 1");
    }
    vector<char> comp_moves;
    cout << "Enter the computer moves as 'r', 'p' or 's'\n";
    for (int i = 0; i < num_moves; ++i)
    {
        char next_move = 0;
        cin >> next_move;
        if (next_move == 'r' || next_move == 'p' || next_move == 's')
        {
            comp_moves.push_back(next_move);
        }
        else
        {
            cout << "Invalid move, use 'r', 'p' or 's'\n";
            --i;
        }
    }

    cout << "***Starting game***\n";
    cout << "Enter r, p or s to play, q to quit\n";
    char player_move = 0;
    int comp_move = 0;
    int p_score = 0;
    int c_score = 0;
    int ties = 0;
    while (true)
    {
        cin >> player_move;
        cout << "Player: " << player_move << " Computer: " << comp_moves[comp_move] << endl;
        switch (player_move)
        {
        case 'r':
            switch (comp_moves[comp_move])
            {
            case 'r':
                ++ties;
                cout << "Tie!\n";
                break;
            case 'p':
                ++c_score;
                cout << "I win!\n";
                break;
            case 's':
                ++p_score;
                cout << "You win!\n";
                break;
            }
            break;
        case 'p':
            switch (comp_moves[comp_move])
            {
            case 'r':
                ++p_score;
                cout << "You win!\n";
                break;
            case 'p':
                ++ties;
                cout << "Tie!\n";
                break;
            case 's':
                ++c_score;
                cout << "I win!\n";
                break;
            }
            break;
        case 's':
            switch (comp_moves[comp_move])
            {
            case 'r':
                ++c_score;
                cout << "I win!\n";
                break;
            case 'p':
                ++p_score;
                cout << "You win!\n";
                break;
            case 's':
                ++ties;
                cout << "Tie!\n";
                break;
            }
            break;
        case 'q':
            return 0;
        default:
            cout << "Invalid move, use 'r', 'p' or 's' to play, 'q' to quit\n";
            break;
        }
        cout << "Score: Player " << p_score << " Computer " << c_score << " Ties " << ties << endl;
        ++comp_move;
        if (comp_move == comp_moves.size())
        {
            comp_move = 0;
        }
    }
    return 0;
}

