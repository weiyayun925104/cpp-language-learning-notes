#include <iostream>
#include <string>

using namespace std;

int main()
{
    string pollQuestion = "";
    cout << "Please enter a poll question that can be answered by: Agree, Disagree, Neither"  << "\n";
    getline(cin, pollQuestion, '\n');

    int agree = 0;
    int disagree = 0;
    int neither = 0;

    bool askingQuestions = true;
    int choice = 0;

    while(askingQuestions)
    {
        cout << pollQuestion << "\n" <<
             "Choices: " << "\n\t" <<
             "1 - Agree" << "\n\t" <<
             "2 - Disagree" << "\n\t" <<
             "3 - Neither" << "\n\t" <<
             "0 - No more questions, please!" << "\n";
        cin >> choice;

        if (choice == 1)
        {
            agree++;
        }
        else if (choice == 2)
        {
            disagree++;
        }
        else if (choice == 3)
        {
            neither++;
        }
        else if (choice == 0)
        {
            askingQuestions = false;
        }
        else
        {
            cout << "That is an invalid answer. Please try again." << "\n";
        }
    }

    string agreeBar = "";
    for (size_t i = 0; i < agree; i++)
    {
        agreeBar += "=";
    }

    string disagreeBar = "";
    for (size_t i = 0; i < disagree; i++)
    {
        disagreeBar += "=";
    }

    string neitherBar = "";
    for (size_t i = 0; i < neither; i++)
    {
        neitherBar += "=";
    }


    cout << "The following are the results of the following survey: " << "\n" <<
         pollQuestion << "\n" <<
         "Agree    (" << agree << "): " << agreeBar << "\n" <<
         "Disagree (" << disagree << "): " << disagreeBar << "\n" <<
         "Neither  (" << neither << "): " << neitherBar << "\n";
}
