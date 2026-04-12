#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Account
{
    const double balance = 1000.0;
    double accountBalance()
    {
        return balance;
    }
    const bool valid = true;
    bool validateAccount()
    {
        return valid;
    }
    const bool securityRules = true;
    bool checkSecurityRules()
    {
        return securityRules;
    }

public:
    friend class Verifier;
};

class Verifier
{
public:
    void verifyAccount(Account &acc)
    {
        if (acc.validateAccount() && acc.checkSecurityRules())
        {
            cout << "Account is valid and meets security rules." << endl;
        }
        else
        {
            cout << "Account verification failed." << endl;
        }
    }
    void auditAccount(Account &acc)
    {
        cout << "Account Balance: " << acc.accountBalance() << endl;
    }
    void generateReport(Account &acc)
    {
        cout << "Report for Account:" << endl;
        verifyAccount(acc);
        auditAccount(acc);
    }
};

int main()
{
    Account myAccount;
    Verifier myVerifier;
    myVerifier.verifyAccount(myAccount);
    myVerifier.auditAccount(myAccount);
    myVerifier.generateReport(myAccount);
    return 0;
}