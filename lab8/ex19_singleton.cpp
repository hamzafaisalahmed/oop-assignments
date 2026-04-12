#include <iostream>
using namespace std;
class Singleton
{
    Singleton() { cout << "created once" << endl; }
    Singleton(const Singleton &) = delete;

public:
    static Singleton &getInstance()
    {
        static Singleton instance;
        return instance;
    }
    void work()
    {
        cout << "Works!" << endl;
    }
};

int main()
{
    Singleton &s1 = Singleton::getInstance();
    s1.work();
    Singleton &s2 = Singleton::getInstance();
    Singleton &s3 = Singleton::getInstance();
    s2.work();
    s3.work();

    cout << &s1 << " " << &s2 << " " << &s3 << endl;
}