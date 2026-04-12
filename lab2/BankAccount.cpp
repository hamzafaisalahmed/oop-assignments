#include <iostream>
#include <string>

using namespace std;
class BankAccount
{
private:
    string name;
    string accountNumber;
    double balance;

public:
    string getName()
    {
        return name;
    }
    string getAccountNumber()
    {
        return accountNumber;
    }
    void setName(string name)
    {
        this->name = name;
    }
    void setAccountNumber(string accountNumber)
    {
        this->accountNumber = accountNumber;
    }

    bool Deposit(double amount)
    {
        if (amount > 0)
        {
            this->balance += amount;
            return true;
        }
        return false;
    }
    bool Withdraw(double amount)
    {
        if (balance - amount >= 0)
        {
            this->balance -= amount;
            return true;
        }
        else
            return false;
    }
    void Display()
    {
        cout << "Account name: " << this->name << "\nAccount number: " << this->accountNumber << "\nAccount balance: " << this->balance << endl;
    }
    BankAccount()
    {
        balance = 0.0;
    }
};

int main()
{
    BankAccount account;
    account.setName("Ali");
    account.setAccountNumber("1234");
    account.Deposit(1000);
    account.Display();
    cout << endl;
    if (account.Withdraw(500))
        cout << "Withdrawal successful!" << endl;
    else
        cout << "Insufficient funds for withdrawal." << endl;
    account.Display();
    if (account.Deposit(-200))
        cout << "Deposit successful!" << endl;
    else
        cout << "Invalid deposit amount." << endl;
    account.Deposit(200);
    account.Display();
}