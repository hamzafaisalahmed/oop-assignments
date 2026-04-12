#include <iostream>
#include <string>
using namespace std;

class Employee
{
private:
    string firstname;
    string lastname;
    double monthlySalary;

public:
    double getMS() { return monthlySalary; }
    void setMS(double ms)
    {
        if (ms > 0)
            monthlySalary = ms;
        else
            monthlySalary = 0.0;
    }
    Employee(string fn, string ln, double ms)
    {
        firstname = fn;
        lastname = ln;
        monthlySalary = ms;
    }
};

int main()
{
    Employee e1("John", "Doe", 3000);
    Employee e2("Jane", "Smith", 4000);
    double s1 = e1.getMS();
    double s2 = e2.getMS();
    cout << "Employee 1 salary: " << s1 << endl;
    cout << "Employee 2 salary: " << s2 << endl;
    s1 *= 1.1;
    s2 *= 1.1;
    e1.setMS(s1);
    e2.setMS(s2);
    cout << "Employee 1 new salary: " << e1.getMS() << endl;
    cout << "Employee 2 new salary: " << e2.getMS() << endl;
}