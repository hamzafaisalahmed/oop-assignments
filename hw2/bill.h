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
    Bill operator+(Bill &other)
    {
        return Bill(other.total + total);
    }
};