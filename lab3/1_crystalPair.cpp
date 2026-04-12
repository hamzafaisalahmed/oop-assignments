#include <iostream>
#include <string>

using namespace std;

class CrystalPair
{
    int *crystalPower;

public:
    CrystalPair()
    {
        crystalPower = new int[2];
        for (int i = 0; i < 2; i++)
        {
            crystalPower[i] = 0;
        }
    }
    CrystalPair(const CrystalPair &other)
    {
        crystalPower = new int[2];
        for (int i = 0; i < 2; i++)
        {
            crystalPower[i] = other.crystalPower[i];
        }
    }
    int sum()
    {
        return crystalPower[0] + crystalPower[1];
    }
    void changePower1(int p)
    {
        crystalPower[0] = p;
    }
    void changePower2(int p)
    {
        crystalPower[1] = p;
    }
    void Display()
    {
        cout << "Crystal 1 Power: " << crystalPower[0] << endl;
        cout << "Crystal 2 Power: " << crystalPower[1] << endl;
    }
};

int main()
{
    CrystalPair one;
    one.changePower1(4);
    one.changePower2(6);
    cout << "one: " << endl;
    one.Display();
    CrystalPair two(one);
    cout << "two: " << endl;
    two.Display();
    cout << "Sum of one: " << one.sum() << endl;
    cout << "Sum of two: " << two.sum() << endl;
    one.changePower1(9);
    cout << "one after change: " << endl;
    one.Display();
    cout << "two after change to 1: " << endl;
    two.Display();
    two.changePower2(9);
    cout << "\n one after change to 2: " << endl;
    one.Display();
    cout << "\n two after change: " << endl;
    two.Display();
}
// shallow copying will be dangerous because it would mean if
// one players crystals are modified then the other ones would be too
// which means they can manipulate each others crystals