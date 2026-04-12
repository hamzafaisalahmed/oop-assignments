#include <iostream>
#include <string>
using namespace std;

class Person
{
protected:
    string name;
    string CNIC;

public:
    Person(string n, string c) : name(n), CNIC(c) {};
    virtual void displayInfo()
    {
        cout << "Name: " << name << endl;
        cout << "CNIC: " << CNIC << endl;
    }
};

class Student : public Person
{
private:
    string rollNumber;
    double GPA;

public:
    Student(string n, string c, string r, double g) : Person(n, c), rollNumber(r), GPA(g) {};
    void displayInfo() override
    {
        Person::displayInfo();
        cout << "Roll Number: " << rollNumber << endl;
        cout << "GPA: " << GPA << endl;
    }
};

class Lecturer : public Person
{
private:
    string employeeID;
    string department;

public:
    Lecturer(string n, string c, string e, string d) : Person(n, c), employeeID(e), department(d) {};
    void displayInfo() override
    {
        Person::displayInfo();
        cout << "Employee ID: " << employeeID << endl;
        cout << "Department: " << department << endl;
    }
};

int main()
{
    Student s("hamza", "12345", "67890", 3.8);
    Lecturer l("Teacher", "22223", "121312", "CS");
    cout << "Student: " << endl;
    s.displayInfo();
    cout << "Lecturer: " << endl;
    l.displayInfo();
}