#include <iostream>

using namespace std;

class BankAccount
{
private:
    double balance;

public:
    BankAccount(double b)
    {
        balance = b;
    }
    void setBalance(double b)
    {
        balance = b;
    }
    double getBalance() { return balance; }
};

class SavingsAccount : protected BankAccount
{
public:
    SavingsAccount(double b) : BankAccount(b) {}
    void addInterest(double rate)
    {
        double x = getBalance() * (1 + rate);
        setBalance(getBalance() + x);
    }
};

int main()
{
    SavingsAccount a(1000);
    a.addInterest(0.08);
    // cout << a.getBalance();
    //  this fails as getBalance is in Bankaccount which is inheritted as protected
}