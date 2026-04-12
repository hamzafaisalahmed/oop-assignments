#include <iostream>
using namespace std;

int main()
{
    int min = 10, max = 50, count = 0;
    auto inRange = [min, max](int val)
    { return (val >= min && val <= max); };
    auto countInRange = [&count, inRange](int val)
    {if (inRange(val)) count++;return count; };
    auto scaleAndCheck = [inRange](auto x, auto factor)
    {if (inRange(x*factor)) return x*factor; else return -1; };

    cout << inRange(12) << endl;
    cout << inRange(199) << endl;
    cout << "Count: " << count << endl;
    cout << countInRange(13) << endl;
    cout << countInRange(200) << endl;
    cout << "New count: " << count << endl;
    cout << scaleAndCheck(2, 20) << endl;
    cout << scaleAndCheck(4, 400) << endl;
}