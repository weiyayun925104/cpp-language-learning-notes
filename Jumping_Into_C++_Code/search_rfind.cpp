#include<iostream>

using namespace std;

int main()
{
    string st = "1111111111";		//10���ַ�
    cout << st.rfind("1111", 9) << endl;	//����6
    cout << st.rfind("1111", 7) << endl;	//����6
    cout << st.rfind("1111", 5) << endl;	//����5
    cout << st.rfind("1111", 2) << endl;	//����2

    return 0;
}
