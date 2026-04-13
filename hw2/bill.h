#include <iostream>
#include <vector>

using namespace std;

class Bill
{
protected:
    double total;

public:
    Bill() : total(0) {}
    Bill(double t) : total(t) {}
    Bill operator+(const Bill &other)
    {
        return Bill(other.total + total);
    }
    friend ostream &operator<<(ostream &os, const Bill &b);
    bool operator==(const Bill &other)
    {
        if (other.total == total)
            return true;
        else
            return false;
    }
    double total()
    {
        return total;
    }
};

ostream &operator<<(ostream &os, const Bill &b)
{
    os << b.total;
    return os;
}