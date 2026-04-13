#include <iostream>
#include <string>
using namespace std;
struct Treatment
{
    string name;
    double cost;
    string staffName;
    void print()
    {
        cout << "Treatment name: " << name << endl;
        cout << "Treatment cost: " << cost << endl;
        cout << "Treatment staff: " << staffName << endl;
    }
};