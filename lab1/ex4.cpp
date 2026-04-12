#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

class Polynomial
{
private:
    int a;
    int b;
    int c;

public:
    string format()
    {
        return to_string(a) + "x^2 + " + to_string(b) + "x + " + to_string(c);
    }
    int getA() { return a; }
    int getB() { return b; }
    int getC() { return c; }

    int eval(int x)
    {
        return (a * x * x) + (b * x) + c;
    }
    Polynomial operator+(Polynomial right)
    {
        return Polynomial(right.getA() + a, b + right.getB(), c + right.getC());
    }
    int &operator[](int index)
    {
        if (index == 0)
        {
            return a;
        }
        else if (index == 1)
        {
            return b;
        }
        else if (index == 2)
        {
            return c;
        }
        else
            exit(0);
    }
    bool operator==(Polynomial right)
    {
        if (a == right.getA() && b == right.getB() && c == right.getC())
            return true;
        else
            return false;
    }

    Polynomial()
    {
        a = 1;
        b = 1;
        c = 1;
    }
    Polynomial(int x, int y, int z)
    {
        a = x;
        b = y;
        c = z;
    }
};

int main()
{
    Polynomial p1(2, 3, 4);
    Polynomial p2(5, 6, 7);
    Polynomial p3 = p1 + p2;
    cout << "P1: " << p1.format() << endl;
    cout << "P2: " << p2.format() << endl;
    cout << "P3: " << p3.format() << endl;
    cout << "P1 evaluated at 2: " << p1.eval(2) << endl;

    p3[0] = 2;
    p3[1] = 3;
    p3[2] = 4;
    cout << "P3 after modifying coefficients: " << p3.format() << endl;
    if (p1 == p3)
    {
        cout << "equal" << endl;
    }
    else
    {
        cout << "Not equal" << endl;
    }
}
