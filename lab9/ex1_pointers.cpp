#include <iostream>
#include <stdexcept>
using namespace std;

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b)
{
    if (b != 0)
        return a / b;
    else
        throw runtime_error("division by zero");
}

double (*ops[])(double, double){add, subtract, multiply, divide};

typedef double (*op)(double, double);

double compute(double a, double b, op o)
{
    return o(a, b);
}

int main()
{
    const double a{15.0}, b{4.0};
    try
    {
        for (int i = 0; i < 4; i++)
        {
            cout << compute(a, b, ops[i]) << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}