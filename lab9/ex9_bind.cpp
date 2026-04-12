#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string formatMessage(const string &prefix, const string &msg, const string &suffix)
{
    return prefix + msg + suffix;
}

int main()
{
    auto makeInfo = bind(formatMessage, "[INFO] ", placeholders::_1, "");
    auto makeError = bind(formatMessage, "[ERROR] ", placeholders::_1, " !!!");
    auto makeDebug = bind(formatMessage, "[DEBUG] ", placeholders::_1, " (line?)");
    vector<function<string(const string &)>> arr = {makeInfo, makeError, makeDebug};
    for (auto x : arr)
    {
        cout << x("Connection timeout") << endl;
    }
    cout << endl;
    vector<string> temp;
    vector<string> msgs = {
        "Msg 1",
        "Msg 2",
        "Msg 3",
        "Msg 4",
        "Msg 5"};
    transform(msgs.begin(), msgs.end(), back_inserter(temp), [makeError](const string &a)
              { return makeError(a); });
    for (auto x : temp)
    {
        cout << x << endl;
    }
}