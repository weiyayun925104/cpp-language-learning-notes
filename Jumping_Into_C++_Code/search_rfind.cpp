#include<iostream>

using namespace std;

int main()
{
    string st = "1111111111";		//10个字符
    cout << st.rfind("1111", 9) << endl;	//返回6
    cout << st.rfind("1111", 7) << endl;	//返回6
    cout << st.rfind("1111", 5) << endl;	//返回5
    cout << st.rfind("1111", 2) << endl;	//返回2

    return 0;
}
