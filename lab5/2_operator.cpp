#include <iostream>

using namespace std;

class shape
{
    double length;
    double width;

public:
    double Area()
    {
        return length * width;
    }
    shape()
    {
        length = 0;
        width = 0;
    }
    shape(double l, double w)
    {
        length = l;
        width = w;
    }
    double operator+(shape &s)
    {
        return s.Area() + this->Area();
    }
};

int main()
{
    shape shape1(0.2, 2.3);
    shape shape2(5.5, 10);
    cout << shape1 + shape2;
}