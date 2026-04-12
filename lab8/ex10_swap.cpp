#include <iostream>

using std::cout, std::endl;
template <typename T>
void swap_values(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

int main()
{
    int x = 5;
    int y = 6;
    cout << "before swap: " << x << y << endl;
    swap_values(x, y);
    cout << "after: " << x << y << endl;
}