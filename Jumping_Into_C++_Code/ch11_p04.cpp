#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct User
{
    string name;
    vector <int> scores;

    int highScore()
    {
        int size = scores.size();
        int highScore = 0;
        for (int i = 0; i < size; i++)
        {
            if (scores.at(i) > highScore)
            {
                highScore = scores.at(i);
            }
        }
        return highScore;
    }
};

void listUsers(User users[], int numberOfUsers);
void allScores(User user);
void allScores(User users[], int numberOfUsers);
void allScoresFromSpecifiedUser(User users[], int numberOfUsers);
void highestScores(User users[], int numberOfUsers);

int main()
{
    User users[50];
    int usersAdded = 0;
    int scoreTemp;

    for (int i = 0; i < 50; i++)
    {
        string result;
        cout << "Please enter your name: \n";
        getline(cin, users[i].name, '\n');

        cout << "Enter scores (0 to stop) : \n";
        for (int j = 0; j < 50; j++)
        {
            cout << "Score: ";
            cin >> scoreTemp;
            if (scoreTemp <= 0)
            {
                break;
            }
            users[i].scores.push_back(scoreTemp);
        }

        usersAdded++;
        cout << "Would you like to enter scores for another user? (Y/N)\n";
        cin >> result;
        cin.clear();
        cin.ignore(80, '\n'); 

        if (result == "N")
        {
            break;
        }

        cout << '\n';
    }
    cout << '\n';
    cout << '\n';

    int option = 0;
    do
    {
        cout << "Please select from the following:\n";
        cout << "(1) Print names of all users\n";
        cout << "(2) Print the highest score from each user\n";
        cout << "(3) Print all scores from a specified user\n";
        cout << "(4) Print all scores from all users\n";
        cout << "(5) Exit\n";
        cout << "=========\n";
        cin >> option;
        cin.clear();
        cin.ignore(80, '\n'); 

        cout << "\n\n";
        switch (option)
        {
        case 1:
            listUsers(users, usersAdded);
            break;
        case 2:
            highestScores(users, usersAdded);
            break;
        case 3:
            allScoresFromSpecifiedUser(users, usersAdded);
            break;
        case 4:
            allScores(users, usersAdded);
            break;
        case 5:
            break;
        default:
            break;
        }
    }
    while (option != 5);
}

void allScoresFromSpecifiedUser(User users[], int numberOfUsers)
{
    cout << "Users:\n";
    int choice = -1;
    for (int i = 0; i < numberOfUsers; i++)
    {
        cout << '(' << i << ") " << users[i].name << '\n';
    }
    do
    {
        cout << "Please choose the user by number to print all scores for.\n";
        cin >> choice;
    }
    while (choice < 0 || numberOfUsers <= choice);

    cin.clear();
    cin.ignore(80, '\n'); 

    cout << "\n\n";
    allScores(users[choice]);
    cout << "\n\n";
}

void listUsers(User users[], int numberOfUsers)
{
    cout << "Users:\n";
    for (int i = 0; i < numberOfUsers; i++)
    {
        cout << users[i].name << '\n';
    }
    cout << "\n\n";
}

void highestScores(User users[], int numberOfUsers)
{
    cout << "Highest score for each user:\n";
    for (int i = 0; i < numberOfUsers; i++)
    {
        cout << users[i].name << ": " << users[i].highScore() << '\n';
    }
    cout << "\n\n";
}

void allScores(User users[], int numberOfUsers)
{
    cout << "All scores for all users:\n";
    for (int i = 0; i < numberOfUsers; i++)
    {
        allScores(users[i]);
    }
}

void allScores(User user)
{
    cout << "All scores for user " << user.name << ":\n";
    int size = user.scores.size();
    for (int scoreIndex = 0; scoreIndex < size; scoreIndex++)
    {
        cout << user.scores.at(scoreIndex) << '\n';
    }
    cout << "\n\n";
}
