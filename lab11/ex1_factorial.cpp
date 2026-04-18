#include <iostream>

int factorial(int n)
{
    std::cout << "Entering factorial (" << n << ")\n";
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

int main()
{
    int f = factorial(5);
    std::cout << "Returning factorial (5) = " << f;
}