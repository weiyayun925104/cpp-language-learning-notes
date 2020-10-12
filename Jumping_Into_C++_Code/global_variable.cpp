#include <iostream>

using namespace std;

int doStuff ()
{
    return 2 + 3;
}

int count_of_function_calls = 0;
void fun ()
{
    count_of_function_calls++;
}
int main ()
{
    fun();
    fun();
    fun();     //全局变量依然有效！
    cout << "Function fun was called " << count_of_function_calls << " times" << endl;
}
