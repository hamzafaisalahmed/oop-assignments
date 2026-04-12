#include <iostream>

using namespace std;

class Person
{
    string EmployeeID;

public:
    virtual void getData()
    {
        string id;
        cout << "Enter ID: ";
        cin >> id;
        EmployeeID = id;
    }
    virtual void DisplayData()
    {
        cout << "ID: " << EmployeeID << endl;
    }
};

class Admin : public Person
{
    string name;
    long long income;

public:
    void getData() override
    {
        Person::getData();
        string n;
        long long i;
        cout << "Enter name: ";
        cin >> n;
        name = n;
        cout << "Enter income: ";
        cin >> i;
        income = i;
    }
    double bonus()
    {
        return income * 0.05;
    }
    void DisplayData() override
    {
        Person::DisplayData();
        cout << "Name: " << name << endl;
        cout << "Monthly income: " << income << endl;
        cout << "Bonus: " << bonus() << endl;
    }
};

class Accounts : public Person
{
    string name;
    long long income;

public:
    void getData() override
    {
        Person::getData();
        string n;
        long long i;
        cout << "Enter name: ";
        cin >> n;
        name = n;
        cout << "Enter income: ";
        cin >> i;
        income = i;
    }
    double bonus()
    {
        return income * 0.05;
    }
    void DisplayData() override
    {
        Person::DisplayData();
        cout << "Name: " << name << endl;
        cout << "Monthly income: " << income << endl;
        cout << "Bonus: " << bonus() << endl;
    }
};
int main()
{
    Admin a;
    a.getData();
    a.DisplayData();
    Accounts b;
    b.getData();
    b.DisplayData();
}