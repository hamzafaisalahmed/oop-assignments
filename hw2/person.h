#include <iostream>
#include <vector>
#include "date.h"
#include "ward.h"
#include "treatment.h"
using namespace std;

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
    }
    Bill generateBill()
    {
        double sum = 500;
        if (ward)
            sum += ward->getDailyRate(); // need to get days and multiply with daily rate
        for (int i = 0; i < treatments.size(); i++)
        {
            sum += treatments[i].cost;
        }
        return Bill(sum);
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

class Employee : public Person
{
protected:
    double salary;
    string department;
    double BillingRate;

public:
    virtual double calculateBillingRate()
    {
        return BillingRate;
    }
};

class GP : public Employee
{
protected:
    // hourly consultation fee
};

class Surgeon : public Employee
{
protected:
    string specialisation;
    // billing rate
};

class Nurse : public Employee
{
protected:
    Ward ward;
    // billing rate
};