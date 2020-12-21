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


class Question
{
private:
    std::string _q;
    std::string _a;
    std::string _b;
    std::string _c;
    std::string _d;

    std::vector<std::string> _answers;

    int _correct;
public:
    Question() : _correct(0)
    {
        initialise();
    }

    Question(const std::string &Q, const std::string &A, const std::string &B,
             const std::string &C, const std::string &D) : _q(Q), _a(A), _b(B), _c(C), _d(D), _correct(0)
    {
        initialise();
    }
    ~Question()
    {
        cleanup();
    }

    void initialise();

    void setQuestion(const std::string &);
    void setA(const std::string &);
    void setB(const std::string &);
    void setC(const std::string &);
    void setD(const std::string &);

    void getQuestion() const;

    bool answer(int);

    bool isCorrect()
    {
        return _correct == 1;
    }

    void cleanup()
    {
        _answers.clear();
    }
};

void Question::initialise()
{
    std::string tmp;
    if (_q.empty())
    {
        std::cout << "Enter a question: ";
        std::cin >> tmp;
        setQuestion(tmp);
    }
    if (_a.empty())
    {
        std::cout << "Enter correct answer: ";
        std::cin >> tmp;
        setA(tmp);
    }
    if (_b.empty())
    {
        std::cout << "Enter first incorrect answer: ";
        std::cin >> tmp;
        setB(tmp);
    }
    if (_c.empty())
    {
        std::cout << "Enter second incorrect answer: ";
        std::cin >> tmp;
        setC(tmp);
    }
    if (_d.empty())
    {
        std::cout << "Enter third incorrect answer: ";
        std::cin >> tmp;
        setD(tmp);
    }

    _answers.push_back(_a);
    _answers.push_back(_b);
    _answers.push_back(_c);
    _answers.push_back(_d);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(_answers.begin(), _answers.end(), std::default_random_engine(seed));
}

void Question::setQuestion(const std::string &Q)
{
    _q = Q;
}
void Question::setA(const std::string &A)
{
    _a = A;
}
void Question::setB(const std::string &B)
{
    _b = B;
}
void Question::setC(const std::string &C)
{
    _c = C;
}
void Question::setD(const std::string &D)
{
    _d = D;
}

void Question::getQuestion() const
{
    std::cout << _q << std::endl << std::endl;

    for (int i = 0; i < _answers.size(); i++)
    {
        std::cout << _answers[i] << std::endl;
    }
    std::cout << std::endl;
}

bool Question::answer(int ans)
{
    ans--;

    if (_answers[ans] == _a)
    {
        _correct = 1;
        return true;
    }
    return false;
}

enum class GameStates { INIT, PLAY, EXIT };

class Quiz
{
private:
    std::vector<Question> _questions;

    GameStates _currentState;

    int _correctAnswers;
public:
    Quiz() : _currentState(GameStates::INIT), _correctAnswers(0) {}

    ~Quiz()
    {
        cleanup();
    }

    void run();

    bool initialise();
    bool setQuestions();

    void gameLoop();

    void askQuestion();

    int checkScore();

    void cleanup();
};


void Quiz::run()
{
    if (_currentState != GameStates::INIT)
    {
        return;
    }
    if (!initialise())
    {
        std::cout << "ERROR: Quiz failed to initialise" << std::endl;
        return;
    }
    gameLoop();
    cleanup();
}
bool Quiz::initialise()
{
    if (!_questions.empty())
    {
        _questions.clear();
        _correctAnswers = 0;
    }
    if (setQuestions())
    {
        return true;
    }
    return false;
}
bool Quiz::setQuestions()
{
    _questions.push_back(
        Question("What...is your name?", "Sir Lancelot of Camelot",
                 "Uh...er...ah...Joe?", "Uh...Princess Peach Fuzz?",
                 "Sir Geldof of Bob?"));
    _questions.push_back(
        Question("What...is your quest?", "To seek the Holy Grail",
                 "To...uh...find the cup of Christ", "To not do well at chess",
                 "To not choose this answer"));
    _questions.push_back(Question("What...is your favourite color?", "Blue",
                                  "Blue! NO! YELLOOOOOOOOWW!!!", "Greeeen?",
                                  "Uh...er...Africa"));
    _questions.push_back(Question(
                             "What...is the capital of Assyria?", "Ninev.hpp", "Used to be Assur",
                             "In the past it was Numrud", "At one time it was at Dur Sarukin"));
    _questions.push_back(
        Question("What...is the airspeed velocity of an unladen swallow?",
                 "An African or European Swallow?", "Uh uh .hpp", "Uh...er...ah",
                 "Well...I don't know..."));

    _currentState = GameStates::PLAY;
    return true;
}
void Quiz::gameLoop()
{
    char choice;

    while (_currentState != GameStates::EXIT)
    {
        askQuestion();
        checkScore();

        std::cout << "You scored: " << _correctAnswers << "/5" << std::endl;
        if (_correctAnswers == 5)
        {
            cout << "I say, jolly well done old chap.\n"; 
        }
        else
        {
            cout << "Better luck next time. Perhaps something with less thinking would be more your style.\n";
        }

        std::cout << "Play Again? ";
        std::cin >> choice;

        if (choice == 'n' || choice == 'N')
        {
            _currentState = GameStates::EXIT;
        }
        else
        {
            initialise();
        }
    }
}
void Quiz::askQuestion()
{
    int choice = 0;

    for (int i = 0; i < _questions.size(); i++)
    {
        std::cout << "Question " << i + 1 << ": ";
        _questions[i].getQuestion();

        std::cout << "Answer (1-4): ";
        std::cin >> choice;

        if (choice < 1 || choice > 4)
        {
            std::cout << "Incorrect choice" << std::endl;
            i--;
            continue;
        }
        _questions[i].answer(choice);
    }
}
int Quiz::checkScore()
{
    for (int i = 0; i < _questions.size(); i++)
    {
        if (_questions[i].isCorrect())
        {
            _correctAnswers++;
        }
    }
    return _correctAnswers;
}
void Quiz::cleanup()
{
    _questions.clear();
    _correctAnswers = 0;
}

int main(int argc, const char *argv[])
{
    try
    {
        Quiz q;

        q.run();

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
