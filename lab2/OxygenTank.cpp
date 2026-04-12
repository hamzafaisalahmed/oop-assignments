#include <iostream>

using namespace std;

class OxygenTank
{

public:
    int oxygenLevel;
    void consume(int units)
    {

        oxygenLevel -= units;
        if (oxygenLevel < 100)
        {
            refill();
            cout << "Oxygen tank refilled!" << endl;
        }
    }
    void refill()
    {
        oxygenLevel = 200;
    }
    OxygenTank()
    {
        oxygenLevel = 200;
    }
};

int main()
{
    OxygenTank o2;
    while (true)
    {
        int choice;
        cout << "Press 1 to exit simulation" << endl;
        cin >> choice;
        if (choice == 1)
            break;
        else
        {
            int consumption;
            cout << "Enter oxygen consumption units: ";
            cin >> consumption;
            o2.consume(consumption);
            cout << "Oxygen level = " << o2.oxygenLevel << endl;
        }
    }
}