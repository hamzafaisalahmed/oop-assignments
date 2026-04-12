#include <iostream>
using namespace std;

class Grounds
{
protected:
    double length;

public:
    Grounds(double l)
    {
        length = l;
    }
    Grounds()
    {
        length = 0;
    }
    virtual double Area()
    {
        cout << "Calculating area of a ground." << endl;
        return -1;
    }
};
class Football : public Grounds
{
public:
    Football(double l) : Grounds(l)
    {
    }
    Football() : Grounds()
    {
    }
    double Area() override
    {
        return length * length;
    }
};
class Cricket : public Grounds
{
public:
    Cricket(double l) : Grounds(l)
    {
    }
    Cricket() : Grounds() {}
    double Area() override
    {
        return length * length * 2;
    }
};
class Robot : public Grounds
{
public:
    Robot(int l) : Grounds(l)
    {
    }
    Robot() : Grounds() {}
    double Area() override
    {
        return 3.14 * length * length;
    }
};

int main()
{
    Grounds g(3);
    cout << g.Area() << endl;
    Football f(2);
    cout << f.Area() << endl;
    Cricket c(2);
    cout << c.Area() << endl;
    Robot r(2);
    cout << r.Area() << endl;
}