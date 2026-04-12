#include <iostream>

using namespace std;

class Payment
{
public:
    virtual void processPayment()
    {
        cout << "Processing a generic payment." << endl;
    }
};

class CreditCardPayment : public Payment
{
public:
    void processPayment() override
    {
        cout << "Processing payment via Credit Card." << endl;
    }
};
class PayPalPayment : public Payment
{
public:
    void processPayment() override
    {
        cout << "Processing payment via PayPal." << endl;
    }
};
class CryptoPayment : public Payment
{
public:
    void processPayment() override
    {
        cout << "Processing payment via Cryptocurrency." << endl;
    }
};

int main()
{
    Payment x;
    x.processPayment();
    CreditCardPayment y;
    y.processPayment();
    PayPalPayment z;
    z.processPayment();
    CryptoPayment a;
    a.processPayment();
}