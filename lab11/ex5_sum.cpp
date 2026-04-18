#include <iostream>

using namespace std;

int sumDigits(int n)
{
    if (n < 10)
        return n;
    return sumDigits(n / 10) + n % 10;
}

int main()
{
    cout << sumDigits(0) << endl
         << sumDigits(9) << endl
         << sumDigits(123) << endl
         << sumDigits(9999) << endl;
}