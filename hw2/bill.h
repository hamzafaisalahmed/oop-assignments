#pragma once
#include <iostream>

struct Bill
{
    double amount;
    Bill(double a) : amount(a) {}
    Bill() : amount(0) {}
    void print() const { std::cout << "Total Bill: " << amount << std::endl; }
    Bill operator+(const Bill &other) const
    {
        return Bill(amount + other.amount);
    }
    bool operator==(const Bill &other) const
    {
        return amount == other.amount;
    }
    bool operator<(const Bill &other) const
    {
        return amount < other.amount;
    }
    bool operator>(const Bill &other) const
    {
        return amount > other.amount;
    }
    double total() const { return amount; }
    friend ostream &operator<<(ostream &os, const Bill &b)
    {
        os << b.amount;
        return os;
    }
    ~Bill() {}
};
