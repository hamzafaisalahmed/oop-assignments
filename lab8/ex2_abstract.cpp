#include <iostream>

using namespace std;

class Account
{
public:
    virtual double calculateInterest() = 0;
};

class SavingsAccount : public Account
{
    double rate;
    double balance;
    double time;

public:
    SavingsAccount(double balance, double rate, double time) : rate(rate), balance(balance), time(time) {}
    double calculateInterest() override
    {
        return balance * rate * time / 12;
    }
};

class CheckingAccount : public Account
{
    double balance;
    double rate;
    double fee;
    double time;

public:
    CheckingAccount(double balance, double rate, double fee, double time) : balance(balance), rate(rate), fee(fee), time(time) {}
    double calculateInterest() override
    {
        return (balance - fee) * rate * time / 12;
    }
};

int main()
{
    Account *savings = new SavingsAccount(5000, 0.03, 6);
    Account *checking = new CheckingAccount(3000, 0.015, 10, 6);
    cout << "Savings Account Interest: " << savings->calculateInterest() << endl;
    cout << "Checking Account Interest: " << checking->calculateInterest() << endl;
}