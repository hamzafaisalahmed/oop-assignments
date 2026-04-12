#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
template <typename T, typename Pred>
vector<T> filter(const vector<T> &v, Pred pred)
{
    vector<T> arr;
    copy_if(v.begin(), v.end(), back_inserter(arr), pred);
    return arr;
}
struct Event
{
    string level;
    string message;
    int code;
};

int main()
{
    int cap = 8;
    vector<Event> events;
    string eventLabels[]{"INFO", "WARN", "ERROR"};
    cout << "Before operations: " << endl;
    for (int i = 0; i < cap; i++)
    {
        Event temp;
        temp.level = eventLabels[i % 3];
        cout << temp.level << " ";
        events.push_back(temp);
    }

    vector<Event> errors;
    errors = filter(events, [](Event e)
                    {if (e.level == "ERROR") return true; else return false; });
    cout << endl
         << "Errors: " << endl;
    for (Event e : errors)
    {
        cout << e.level << " ";
    }
    cout << endl;
    events.erase(remove_if(events.begin(), events.end(), [](Event e)
                           {
        if (e.level == "INFO")
            return true;
        else
            return false; }),
                 events.end());
    cout << "After operations: " << endl;
    for (Event e : events)
    {
        cout << e.level << " ";
    }
    cout << endl;
}