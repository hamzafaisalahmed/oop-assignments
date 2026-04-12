#include <iostream>
#include <stdexcept>
using namespace std;

class Person
{
    string name;
    int age;

public:
    Person(const string &name, int age) : name(name), age(age)
    {
        if (age < 0)
            throw invalid_argument("Age cannot be negative");
        cout << "Person constructor called" << endl;
    }
    virtual void display()
    {
        cout << "Name: " << name << "\nAge: " << age << "\n";
    }
    virtual string getRole() { return "Person"; }
    virtual ~Person() { cout << "Person destructor called" << endl; }
};

class Student : virtual public Person
{
public:
    Student(const string &n, int a)
        : Person(n, a)
    {
        cout << "Student constructor called\n";
    }
    string getRole() override { return "Student"; }
    void display() override
    {
        Person::display();
        cout << "is a student" << endl;
    }
};

class Employee : virtual public Person
{
public:
    Employee(const string &n, int a)
        : Person(n, a)
    {
        cout << "Employee constructor called\n";
    }
    string getRole() override { return "Employee"; }
    void display() override
    {
        Person::display();
        cout << "is an employee" << endl;
    }
};

class TeachingAssistant : public Student, public Employee
{
public:
    TeachingAssistant(const string &n, int a)
        : Person(n, a), Student(n, a), Employee(n, a)
    {
        cout << "TeachingAssistant constructor called\n";
    }
    string getRole() override { return "TA"; }
    void display() override
    {
        Person::display();
        cout << "is a teaching assistant" << endl;
    }
};

void testDiamondProblem()
{
    try
    {
        TeachingAssistant ta("person1", 19);
        cout << endl;
        Person *ptr = &ta;
        ptr->display();
        cout << "Role: " << ptr->getRole() << endl;
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    try
    {
        TeachingAssistant invalid("Ghost", -5);
    }
    catch (const invalid_argument &e)
    {
        cout << "Exception: " << e.what() << endl;
    }
    cout << endl;
}

int main()
{
    testDiamondProblem();
    return 0;
}
