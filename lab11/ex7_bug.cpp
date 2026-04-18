#include <iostream>
#include <vector>
using namespace std;

// int factorial(int n)
// {
//     return n * factorial(n - 1); // missing base case
// }

// calling factorial 3 will cause infinite recursion

int factorial(int n)
{
    if (n < 1)
        return 1;
    return n * factorial(n - 1);
}

// string reverse(const string &s)
// {
//     if (s.size() == 0)
//         return s;
//     return s[0] + reverse(s.substr(1)); // wrong order
// }

// returns abc beacuse we print s[0] first, which on first call will be a, then b and c

string reverse(const string &s)
{
    if (s.size() == 0)
        return s;
    return reverse(s.substr(1)) + s[0]; // wrong order
}

// int sum(const vector<int> &arr, int i = 0)
// {
//     if (i == (int)arr.size())
//         return 0;
//     return sum(arr, i + 1); // forgets to include arr [i]
// }
// this will return 0 as thats the only thing being returned
int sum(const vector<int> &arr, int i = 0)
{
    if (i == (int)arr.size())
        return 0;
    return arr[i] + sum(arr, i + 1);
}

int main()
{
    cout << factorial(3) << endl;
    cout << reverse("abc") << endl;
    cout << sum({1, 2, 3}) << endl;
}