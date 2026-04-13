#include <iostream>
#include <string>
#include "person.h"
#include <vector>
#include "date.h"
#include "ward.h"
#include "treatment.h"
#include "bill.h"
using namespace std;
// assumes current date will be global variable
extern Date currentDate;

// add totalBill logic
class Person
{
protected:
    string name;
    Date dob;
    int id;
    string contact;

public:
    Person(string n, Date d, int i, string c) : name(n), dob(d), id(i), contact(c) {}
    virtual void display()
    {
        cout << "Name: " << name << endl;
        cout << "Date of birth: ";
        dob.displayDate();
        cout << "ID: " << id << endl;
        cout << "Contact: " << contact << endl;
    }
    virtual ~Person() {}
};

class Patient : public Person
{
protected:
    string diagnosis;
    Date admission;
    Ward *ward;
    vector<Treatment> treatments;
    bool isDischarged;
    bool isCritical;
    bool scheduledOperation;

public:
    Patient(string n, Date d, int i, string c, string diag, Date adm, bool crit) : Person(n, d, i, c), diagnosis(diag), admission(adm), isDischarged(false), isCritical(crit), scheduledOperation(false) {}
    void display() override
    {
        Person::display();
        cout << "Diagnosis: " << diagnosis << endl;
        cout << "Date of admission: ";
        admission.displayDate();
        cout << "Ward: ";
        if (ward)
            cout << ward->getName() << endl;
        else
            cout << "N/A" << endl;
        // treatments
        for (int i = 0; i < treatments.size(); i++)
        {
            treatments[i].print();
        }
        if (isCritical)
            cout << "Critical" << endl;
        if (scheduledOperation)
            cout << "Operation scheduled" << endl;
        if (isDischarged)
            cout << "Discharged" << endl;
    }
    Bill generateBill()
    {
        double sum = 500;
        int days = calculateDays(currentDate, admission);
        if (ward)
            sum += (ward->getDailyRate() * days); // need to get days and multiply with daily rate
        for (int i = 0; i < treatments.size(); i++)
        {
            sum += treatments[i].cost;
        }
        return Bill(sum);
    }
    Bill totalBill()
    {
        return generateBill();
    }
    void addTreatment(Treatment t)
    {
        treatments.push_back(t);
    }
    int treatmentCount()
    {
        return treatments.size();
    }
    void setWard(Ward *w)
    {
        ward = w;
    }
    bool getIsCritical()
    {
        return isCritical;
    }
    bool getScheduledOperation()
    {
        return scheduledOperation;
    }
    void scheduleOperation()
    {
        scheduledOperation = true;
    }
};

class StaffMember : public Person
{
protected:
    double salary;
    string department;

public:
    StaffMember(string n, Date d, int i, string c, double sal, string dept) : Person(n, d, i, c), salary(sal), department(dept) {}
    virtual double calculateBillingRate() = 0;
    virtual void display() override
    {
        Person::display();
        cout << "Salary: Rs." << salary << endl;
        cout << "Department: " << department << endl;
    }
};

class GP : public StaffMember
{
public:
    GP(string n, Date d, int i, string c, double sal, string dept) : StaffMember(n, d, i, c, sal, dept) {}
    // hourly consultation fee
    double calculateBillingRate() override
    {
        return 500;
    }
    void display() override
    {
        StaffMember::display();
        cout << "Hourly consultation fee: " << 500;
    }
};

class Surgeon : public StaffMember
{
protected:
    string specialisation;
    // billing rate
public:
    Surgeon(string n, Date d, int i, string c, double sal, string dept, string s) : StaffMember(n, d, i, c, sal, dept), specialisation(s) {}
    double calculateBillingRate() override
    {
        return 1000;
    }
    void display() override
    {
        StaffMember::display();
        cout << "Per operation fee: " << 1000;
    }
};

class Nurse : public StaffMember
{
protected:
    Ward *ward;
    // billing rate
public:
    Nurse(string n, Date d, int i, string c, double sal, string dept, double f, Ward *w) : StaffMember(n, d, i, c, sal, dept), ward(w) {}
    double calculateBillingRate() override
    {
        return 200;
    }
    void display() override
    {
        StaffMember::display();
        cout << "Hourly care fee: " << 200;
    }
};