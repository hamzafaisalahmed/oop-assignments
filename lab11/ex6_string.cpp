#include <iostream>
#include <string>

using namespace std;

int countChar(const string &s, char c, int i = 0)
{
    if (s.size() == i)
    {
        return 0;
    }
    if (s[i] == c)
        return 1 + countChar(s, c, i + 1);
    else
        return countChar(s, c, i + 1);
}

string removeChar(const string &s, char c)
{
    if (s.size() == 0)
    {
        return "";
    }
    char f = s[0];
    string rest = s.substr(1);
    if (f != c)
        return f + removeChar(rest, c);
    else
        return removeChar(rest, c);
}

string toBinary(int n)
{
    if (n == 0 || n == 1)
        return to_string(n);
    int t = n % 2;
    if (t == 0)
        return toBinary(n / 2) + "0";
    else
        return toBinary(n / 2) + "1";
}

int main()
{
    cout << countChar("banana", 'a') << endl;
    cout << removeChar("hello world", 'l') << endl;
    cout << toBinary(10) << endl;
}