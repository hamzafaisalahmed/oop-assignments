#include <iostream>

using namespace std;

void countdown(int n)
{
    if (n != 0)
    {
        cout << n << endl;
        countdown(n - 1);
    }
    else
        cout << "Go!" << endl;
}

void countup(int n)
{
    if (n != 0)
    {
        countup(n - 1);
        cout << n << endl;
    }
    else
        cout << "Go!" << endl;
}

int main()
{
    countdown(5);
    cout << endl;
    countup(5); // as all the numbers are first pushed on to stack, so when it starts popping, it starts with Go! then 1 ,2 and so on. before this it was printing before pushing on to stack.
}