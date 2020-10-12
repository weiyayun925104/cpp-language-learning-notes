
#include <iostream>
#include <string>

using namespace std;

string currentDay(int dayNumber);

int main()
{
	for (size_t i = 1; i <= 12; i++)
	{
		string day = currentDay(i);
		cout << "On the " << day << " day of Christmas, " <<
			"My true love sent to me\n";

		switch (i)
		{
			case 12:
				cout << "Twelve drummers drumming,\n";
			case 11:
				cout << "Eleven pipers piping,\n";
			case 10:
				cout << "Ten lords a-leaping,\n";
			case 9:
				cout << "Nine ladies dancing,\n";
			case 8:
				cout << "Eight maids a-milking,\n";
			case 7:
				cout << "Seven swans a-swimming,\n";
			case 6:
				cout << "Six geese a-laying,\n";
			case 5:
				cout << "Five golden rings,\n";
			case 4:
				cout << "Four calling birds,\n";
			case 3:
				cout << "Three French hens,\n";
			case 2:
				cout << "Two turtle doves,\n";
			default:
				break;
		}

		string ending = " partridge in a pear tree.\n\n";
		if (i == 1)
		{
			ending = "A" + ending;
		}
		else
		{
			ending = "And a" + ending;
		}
		cout << ending;
	}
}

string currentDay(int dayNumber)
{
	string day = "";
	switch (dayNumber)
	{
	case 1:
		day = "first";
		break;
	case 2:
		day = "second";
		break;
	case 3:
		day = "third";
		break;
	case 4:
		day = "fourth";
		break;
	case 5:
		day = "fifth";
		break;
	case 6:
		day = "sixth";
		break;
	case 7:
		day = "seventh";
		break;
	case 8:
		day = "eighth";
		break;
	case 9:
		day = "ninth";
		break;
	case 10:
		day = "tenth";
		break;
	case 11:
		day = "eleventh";
		break;
	case 12:
		day = "twelfth";
		break;
	}
	return day;
}
