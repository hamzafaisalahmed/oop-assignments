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

public:
    void display() override
    {
        Person::display();
        cout << "Diagnosis: " << diagnosis << endl;
        cout << "Date of admission: ";
        admission.displayDate();
        cout << "Ward: ";
        // finish for ward and treatments
    }
    Bill generateBill()
    {
        double sum = 500;
        sum += ward->getDailyRate();
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