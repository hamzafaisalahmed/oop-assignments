#include <iostream>
#include <functional>
using namespace std;

function<int()> makeCounter(int start, int step)
{
    return [start, step]() mutable
    {start+= step; return start; };
}

int main()
{
    auto byOne = makeCounter(0, 1);
    auto byFive = makeCounter(0, 5);
    auto countdown = makeCounter(20, -3);

    for (int i = 0; i < 5; i++)
    {
        cout << "By One value " << i + 1 << ": " << byOne() << endl;
        cout << "By Five value " << i + 1 << ": " << byFive() << endl;
        cout << "Countdown value " << i + 1 << ": " << countdown() << endl;
        cout << "____________________________________________________" << endl;
    }
}