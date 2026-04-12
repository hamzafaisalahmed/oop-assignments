#include <iostream>

using namespace std;

template <typename T, typename U, typename V>
auto max(T a, U b, V c)
{
    auto maxVal = a;
    if (b > maxVal)
        maxVal = b;
    if (c > maxVal)
        maxVal = c;
    return maxVal;
}

int main()
{
    cout << max('3', 5, 7.6) << endl;
}