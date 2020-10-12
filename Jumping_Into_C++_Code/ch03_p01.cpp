#include <iostream>
#include <string>

using namespace std;

int main()
{
	string name;
	cout << "Please enter your name: " << endl;
	getline(cin, name, '\n'); 
	cout << "Your name is: " << name << "\n";

	double number1 = 0;
	double number2 = 0;
	cout << "Please enter two numbers to add together. \nFirst Number : ";
	cin >> number1;
	cout << "Second Number : ";
	cin >> number2;

	double result = number1 + number2;
	cout << "The result is:\n" << number1 << " + " << number2 << " = " << result << "\n";

	cout << "Please enter two numbers to divide together. \nNumerator : ";
	cin >> number1;
	cout << "Denominator : ";
	cin >> number2;
	result = number1 / number2;
	cout << "The result is:\n" << number1 << " / " << number2 << " = " << result << endl;
}
