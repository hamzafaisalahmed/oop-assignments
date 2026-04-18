#include <iostream>

using namespace std;

double power(double b, double e)
{
    if (e == 0)
        return 1;
    if (e < 0)
    {
        return 1 / b * power(b, e + 1);
    }
    return b * power(b, e - 1);
}

int main()
{
    cout << "power(2,0): " << power(2, 0) << endl;
    cout << "power(2,5): " << power(2, 5) << endl;
    cout << "power(3,3): " << power(3, 3) << endl;
    cout << "power(10,4): " << power(10, 4) << endl;

    cout << "power(2.0,-3): " << power(2.0, -3) << endl;
}