#include <iostream>

using namespace std;

int main()
{
    const int Lbs_per_stn = 14;

    cout << "Enter your weight in pounds: ";
    int lbs = 0;
    cin >> lbs;
    int stone = lbs / Lbs_per_stn;
    int pounds = lbs % Lbs_per_stn;
    cout << lbs << " pounds are " << stone << " stone, " << pounds << " pound(s).\n";

    return 0;
}
