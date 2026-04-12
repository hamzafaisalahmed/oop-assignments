#include <iostream>

using namespace std;

int josephus(int n, int m)
{
    if (n == 1)
        return 0;
    return (josephus((n - 1), m) + m) % n;
}

int main()
{
    cout << "Enter number of players: ";
    int players;
    cin >> players;
    cout << "Enter step to eliminate: ";
    int m;
    cin >> m;
    cout << "Safe position: " << josephus(players, m);
}