#include <iostream>

using namespace std;

int multiply(int a, int b)
{
    return a * b;
}
int multiply(int a, int b, int c)
{
    return a * b * c;
}
double multiply(double a, double b)
{
    return a * b;
}
double multiply(double a, double b, double c)
{
    return a * b * c;
}

int main()
{
    int x = 2;
    int y = 3;
    int z = 4;
    double a = 1.5;
    double b = 2.5;
    double c = 3.5;
    cout << multiply(x, y) << endl;
    cout << multiply(x, y, z) << endl;
    cout << multiply(a, b) << endl;
    cout << multiply(a, b, c) << endl;
}