#include <iostream>
#include <string>

using namespace std;

class Employee
{
protected:
    int employeeID;
    double baseSalary;

public:
    Employee(int id, double s) : employeeID(id), baseSalary(s) {}
    virtual void display()
    {
        cout << "Employee ID: " << employeeID << endl;
        cout << "Base Salary: " << baseSalary << endl;
        cout << "Bonus: " << 0.05 * baseSalary << endl;
    }
};

class Manager : public Employee
{
private:
    string department;

public:
    Manager(int id, double s, string d) : Employee(id, s), department(d) {}
    void display() override
    {
        cout << "Employee ID: " << employeeID << endl;
        cout << "Base Salary: " << baseSalary << endl;
        cout << "Department: " << department << endl;
        cout << "Bonus: " << 0.1 * baseSalary << endl;
    }
    string getDepartment() { return department; }
};

class RegionalDirector : public Manager
{
private:
    string region;

public:
    RegionalDirector(int id, double s, string d, string r) : Manager(id, s, d), region(r) {}
    void display() override
    {
        cout << "Employee ID: " << employeeID << endl;
        cout << "Base Salary: " << baseSalary << endl;
        cout << "Department: " << getDepartment() << endl;
        cout << "Region: " << region << endl;
        cout << "Bonus: " << baseSalary * 0.15 << endl;
    }
};

int main()
{
    Employee e(123, 1000);
    Manager m(456, 1000, "CS");
    RegionalDirector r(789, 1000, "Math", "Karachi");
    e.display();
    cout << endl;
    m.display();
    cout << endl;
    r.display();
}