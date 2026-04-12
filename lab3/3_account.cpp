#include <iostream>
#include <string>
using namespace std;

class Account
{
    string account_no;
    double account_balance;
    string security_code;

public:
    void initializeAndDisplay()
    {
        account_no = "0000001";
        account_balance = 0.0;
        security_code = "0000";
        cout << "Account Number: " << account_no << endl;
        cout << "Account Balance: " << account_balance << endl;
        cout << "Security Code: " << security_code << endl;
    }
    void setAccountNo(const string &acc_no)
    {
        account_no = acc_no;
    }
    void setAccountBalance(double balance)
    {
        account_balance = balance;
    }
    void setSecurityCode(const string &sec_code)
    {
        security_code = sec_code;
    }
};

int main()
{
    Account myAccount;
    myAccount.initializeAndDisplay();
    return 0;
}