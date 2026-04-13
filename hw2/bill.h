#include <iostream>
#include <vector>

using namespace std;

class Bill
{
protected:
    double totalBill;

public:
    Bill() : totalBill(0) {}
    Bill(double t) : totalBill(t) {}
    Bill operator+(const Bill &other) const
    {
        return Bill(other.totalBill + totalBill);
    }
    friend ostream &operator<<(ostream &os, const Bill &b);
    bool operator==(const Bill &other) const
    {
        if (other.totalBill == totalBill)
            return true;
        else
            return false;
    }
    double total()
    {
        return totalBill;
    }
};

ostream &operator<<(ostream &os, const Bill &b)
{
    os << b.totalBill;
    return os;
}