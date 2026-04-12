#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include <algorithm>

using namespace std;

template <typename F>
auto compose(F f) { return f; }

template <typename F, typename... rest>
auto compose(F f, rest... g)
{
    return [=](auto x)
    { return f(compose(g...)(x)); };
}

int main()
{
    // demo:
    auto f = [](int x)
    { return x * 10; };
    auto g = [](int y)
    { return y * 2; };
    auto fg = compose(f, g);
    cout << "fg: " << fg(2) << endl;
    auto h = [](int z)
    { return z / 10; };
    auto hfg = compose(h, f, g);
    cout << "hfg: " << hfg(2) << endl;

    auto negate = [](int x)
    { return x * -1; };
    auto addTen = [](int x)
    { return x + 10; };
    auto square = [](int x)
    { return x * x; };

    auto composed = compose(negate, addTen, square);
    vector<int> v = {1, 2, 3, 4, 5};
    vector<int> ans;
    transform(v.begin(), v.end(), back_inserter(ans), composed);
    for (auto x : ans)
    {
        cout << x << endl;
    }
    cout << endl;

    function<long long(int)> fib;
    fib = [&fib](int n) -> long long
    {
        if (n <= 1 && n >= 0)
            return n;
        return fib(n - 2) + fib(n - 1);
    };
    cout << "Fibonacci numbers: " << endl;
    for (int i = 0; i <= 10; i++)
    {
        cout << "Fib(" << i << "): " << fib(i) << endl;
    }
}