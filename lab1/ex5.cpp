#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Glass
{
public:
    int LiquidLevel;
    void Drink(int mm)
    {
        LiquidLevel -= mm;
    }
    void Refills()
    {
        LiquidLevel = 200;
    }

    Glass()
    {
        LiquidLevel = 200;
    }
};

int main()
{
    Glass glass;
    while (true)
    {
        cout << "Enter command: ";
        string cmd;
        cin >> cmd;
        if (cmd == "terminate")
            break;
        else if (cmd == "drink")
        {
            int amount;
            cout << "Amount to drink: ";
            cin >> amount;
            glass.Drink(amount);
        }
        if (glass.LiquidLevel < 100)
            glass.Refills();
        cout << "Current liquid level: " << glass.LiquidLevel << endl;
    }
}