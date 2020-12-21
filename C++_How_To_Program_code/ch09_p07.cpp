#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <numeric>
#include <iomanip>
#include <chrono>
#include <memory>
#include <utility>
#include <random>
#include <limits>
#include <type_traits>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include<climits>
#include <ctime>
#include <cmath>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::vector;
using std::list;
using std::set;
using std::multiset;
using std::map;
using std::multimap;
using std::pair;
using std::string;
using std::getline;
using std::to_string;
using std::domain_error;
using std::runtime_error;
using std::exception;
using std::transform;
using std::back_inserter;
using std::ostream_iterator;
using std::search;
using std::sort;
using std::copy;
using std::accumulate;
using std::find;
using std::find_if;
using std::max;
using std::min;
using std::swap;
using std::stable_partition;
using std::streamsize;
using std::setprecision;
using std::setw;
using std::chrono::steady_clock;
using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;
using std::distance;
using std::unique;
using std::mt19937;
using std::uniform_int_distribution;
using std::ios_base;
using std::showbase;
using std::hex;
using std::oct;
using std::dec;
using std::fixed;
using std::scientific;
using std::left;
using std::numeric_limits;
using std::common_type;
using std::reverse;

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

int nrand_one(int n, mt19937 &e)
{
    if (n <= 0)
    {
        throw domain_error("Argument to nrand is out of range");
    }
    uniform_int_distribution<int> d(0, n - 1);
    return d(e);
}

int nrand_two(int m, int n, mt19937 &e)
{
    if (n <= m)
    {
        throw domain_error("Argument to nrand is out of range");
    }
    uniform_int_distribution<int> d(m, n - 1);
    return d(e);
}

inline std::ios_base &general(std::ios_base &b)
{
    b.setf(std::ios_base::fmtflags(0), std::ios_base::floatfield);
    return b;
}

template<typename T>
ostream &print_vector(const vector<T> &v, ostream &os)
{
    if (v.size() > 0)
    {
        os << v[0];

        for (typename vector<T>::size_type i = 1; i < v.size(); i++)
        {
            os << ", " << v[i];
        }

        os << endl;
    }

    return os;
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    if (v.size() > 0)
    {
        os << "{ ";
        os << v[0];

        for (typename vector<T>::size_type i = 1; i < v.size(); i++)
        {
            os << ", " << v[i];
        }

        os << " }";
    }

    return os;
}

template<typename T>
istream &operator>>(istream &is, vector<T> &d)
{
    char ch1;
    char ch2;
    T temp;
    vector<T> v_temp;
    is >> ch1;
    if (!is)
    {
        return is;
    }
    if (ch1 != '{')
    {
        is.clear(ios_base::failbit);
        return is;
    }
    while (is >> temp && is >> ch2)
    {
        if (ch2 == ',')
        {
            v_temp.push_back(temp);
        }
        else if (ch2 == '}')
        {
            v_temp.push_back(temp);
            d = v_temp;
            return is;
        }
        else
        {
            is.clear(ios_base::failbit);
            return is;
        }
    }

    return is;
}

enum suit_t {HEART, DIAMOND, SPADE, CLUB};

vector <int> dealhand();
vector <int> assign_value(vector <int>   &hand);
vector <int> assign_suit(vector <int>   &hand);
void analyze_hand (vector <int> &hand_value, vector <int> &hand_suit);
void print_result (void);

bool hand_straight, hand_royal_flush, hand_flush, hand_four, hand_three;
int hand_pairs;

#define NUM_RANKS 13
#define NUM_SUITS    4
#define NUM_CARDS 5

void analyze_hand (vector <int> &hand_value, vector <int> &hand_suit)
{
    int num_in_rank[NUM_RANKS] = {0};
    int num_in_suit[NUM_SUITS] = {0};

    int rank, suit;
    int size = hand_suit.size();
    for(int i = 0; i < size; i++)
    {
        suit = hand_suit.at(i);
        rank = hand_value.at(i);
        num_in_rank[rank]++;
        num_in_suit[suit]++;
    }

    hand_straight = false;
    hand_royal_flush = false;
    hand_flush = false;
    hand_four = false;
    hand_three = false;
    hand_pairs = 0;

    /* check for flush */
    for (suit = 0; suit < NUM_SUITS; suit++)
    {
        if (num_in_suit[suit] == NUM_CARDS)
        {
            hand_flush = true;
        }
    }

    int num_consec = 0;
    /* checks for royal flush */
    if (hand_flush)
    {
        for (rank = 8; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)
        {
            num_consec++;
        }
        if (num_consec == NUM_CARDS)
        {
            hand_royal_flush = true;
            return;
        }
    }

    num_consec = 0;
    /* check for straight */
    rank = 0;
    while (num_in_rank[rank] == 0)
    {
        rank++;
    }

    for (; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)
    {
        num_consec++;

        /* special case: low-straight */
        if (num_consec == 4 && rank == 3 && num_in_rank[12] > 0)
        {
            hand_straight = true;
            return;
        }
    }

    if (num_consec == NUM_CARDS)
    {
        hand_straight = true;
        return;
    }

    /* check for 4-of-a-kind, 3-of-a-kind, and pairs */
    for (rank = 0; rank < NUM_RANKS; rank++)
    {
        if (num_in_rank[rank] == 4)
        {
            hand_four = true;
        }
        if (num_in_rank[rank] == 3)
        {
            hand_three = true;
        }
        if (num_in_rank[rank] == 2)
        {
            hand_pairs++;
        }
    }
}
void print_result (void)
{
    if (hand_royal_flush)
    {
        cout << "Royal flush";
    }
    else if (hand_straight && hand_flush)
    {
        cout <<  "Straight flush";
    }
    else if (hand_four)
    {
        cout << "Four of a kind";
    }
    else if (hand_three && hand_pairs == 1)
    {
        cout << "Full house";
    }
    else if (hand_flush)
    {
        cout << "Flush";
    }
    else if (hand_straight)
    {
        cout << "Straight";
    }
    else if (hand_three)
    {
        cout << "Three of a kind";
    }
    else if (hand_pairs == 2)
    {
        cout << "Two pairs";
    }
    else if (hand_pairs == 1)
    {
        cout << "Pair";
    }
    else
    {
        cout << "High card";
    }

    cout <<  "\n";
}
std::random_device rd;
std::mt19937 gen(rd());

int getRandomNumber(const int &min, const int &max)
{
    return std::uniform_int_distribution<int> {min, max}(gen);
}

vector <int> dealhand()
{
    int r;
    vector <int> deck;
    vector <int> hand;

    for (int i = 0; i < 52; i++)
    {
        deck.push_back(i + 1);
    }

    for (int i = 0; i < NUM_CARDS; i++)
    {
        do
        {
            r = getRandomNumber(0, 51);
        }
        while (deck.at(r) == 0);
        deck.at(r) = 0;
        hand.push_back(r);
    }
    return hand;
}
vector <int> assign_suit(vector <int> &hand)
{
    vector <int> hand_suit;
    int size = hand.size();
    for(int i = 0; i < size; i++)
    {
        int r = hand.at(i);
        if (r < 13)
        {
            hand_suit.push_back(HEART);
        }
        else if (r < 26)
        {
            hand_suit.push_back(DIAMOND);
        }
        else if (r < 39)
        {
            hand_suit.push_back(SPADE);
        }
        else if (r < 52)
        {
            hand_suit.push_back(CLUB);
        }
        else
        {
            cout << "Error in assigning values in hand";
        }
    }
    return hand_suit;
}
vector <int> assign_value(vector <int> &hand)
{
    vector <int> hand_value;
    int size = hand.size();
    for(int i = 0; i < size; i++)
    {
        int r = hand.at(i);
        if (r < 13)
        {
            hand_value.push_back(r);
        }
        else if (r < 26)
        {
            hand_value.push_back(r - 13);
        }
        else if (r < 39)
        {
            hand_value.push_back(r - 26);
        }
        else if (r < 52)
        {
            hand_value.push_back(r - 39);
        }
        else
        {
            cout << "Error in assigning values in hand";
        }
    }
    return hand_value;
}

int main(int argc, const char *argv[])
{
    try
    {
        const char *rank_code[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
        const char *suit_code[] = {"Hearts", "Diamonds", "Spades", "Clubs"};

        vector <int> hand_prelim;
        vector <int> hand_suit;
        vector <int> hand_value;

        hand_prelim = dealhand();
        hand_suit = assign_suit(hand_prelim);
        hand_value = assign_value(hand_prelim);


        int rank, suit;
        int size = hand_suit.size();
        for(int i = 0; i < size; i++)
        {
            suit = hand_suit.at(i);
            rank = hand_value.at(i);
            cout << rank_code[rank] << " of " << suit_code[suit] << "\n";
        }
        analyze_hand (hand_value, hand_suit);
        cout <<  "\n";
        print_result ();

        return 0;
    }
    catch (exception &e)
    {
        cerr << "error: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        cerr << "Oops: unknown exception!\n";
        return 2;
    }
}
