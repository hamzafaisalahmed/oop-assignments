#include <iostream>
#include <functional>
#include <vector>
using namespace std;

class Multiplier
{
private:
    double factor;
    int callCount;

public:
    Multiplier(double f) : factor(f), callCount(0) {}
    double operator()(double x)
    {
        callCount++;
        return x * factor;
    }
    int getCount() { return callCount; }
};

void dispatch(double val, vector<function<double(double)>> &handlers)
{
    for (int i = 0; i < handlers.size(); i++)
    {
        cout << handlers[i](val) << endl;
    }
}

int main()
{
    Multiplier a(2), b(3), c(5);
    vector<function<double(double)>> handler;
    handler.push_back(ref(a));
    handler.push_back(ref(b));
    handler.push_back(ref(c));
    dispatch(6.0, handler);
    cout << a.getCount() << endl
         << b.getCount() << endl
         << c.getCount();
}