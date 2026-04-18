#include <iostream>

int counter = 0;

int fib(int n)
{
    counter++;
    if (n == 0 || n == 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main()
{
    int arr[]{1, 5, 10, 15, 20};
    std::cout << "n \tfib(n) total calls to fib" << std::endl;
    for (auto &x : arr)
    {
        counter = 0;
        std::cout << x << "\t" << fib(x) << "\t" << counter << std::endl;
    } // it grows quickly because it grows exponentially as n increases
}