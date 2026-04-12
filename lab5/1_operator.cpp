#include <iostream>

using namespace std;

class Test
{
    int x;

public:
    Test()
    {
        x = 0;
    }
    Test(int x)
    {
        this->x = x;
    }
    void operator--()
    {
        x *= 4;
    }
    void operator--(int)
    {
        x /= 4;
    }
    void Display()
    {
        cout << x << endl;
    }
};

int main()
{
    Test x(2);
    --x;
    x.Display();
    x--;
    x.Display();
}