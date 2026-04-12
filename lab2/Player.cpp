#include <iostream>
#include <string>
using namespace std;

class Player
{
    string firstName;
    string lastName;
    double monthlyContract;

public:
    void editContract(double mc)
    {
        if (mc < 0)
            monthlyContract = 0.0;
        else
            monthlyContract = mc;
    }
    Player(string fn, string ln, double mc)
    {
        firstName = fn;
        lastName = ln;
        if (mc < 0)
            monthlyContract = 0.0;
        else
            monthlyContract = mc;
    }
    double yearlyEarnings()
    {
        return monthlyContract * 12;
    }
    void Bonus()
    {
        monthlyContract = monthlyContract * 1.1;
    }
};

int main()
{
    Player obj1("jawwad", "farid", 10000.24);
    Player obj2("ali", "ahmed", -5000);
    cout << "Yearly earnings: " << obj1.yearlyEarnings() << endl;
    cout << "Yearly earnings: " << obj2.yearlyEarnings() << endl;
    obj2.editContract(100);
    obj1.Bonus();
    cout << "yearly earnings of obj1: " << obj1.yearlyEarnings() << endl;
    obj2.Bonus();
    cout << "yearly earnings of obj2: " << obj2.yearlyEarnings() << endl;
}