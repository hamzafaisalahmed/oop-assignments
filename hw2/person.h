#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "date.h"
#include "treatment.h"
#include "bill.h"

class Ward;
class Patient;

class Person
{
protected:
    std::string name;
    Date dob;
    int id;
    std::string contact;

public:
    Person(std::string n, Date d, int i, std::string c);
    virtual void display();
    virtual ~Person();
};

class Patient : public Person
{
protected:
    std::string diagnosis;
    Date admission;
    Ward *ward;
    std::vector<Treatment> treatments;
    bool isDischarged;
    bool isCritical;
    bool scheduledOperation;

public:
    Patient(std::string n, Date d, int i, std::string c, std::string diag, Date adm, bool crit);
    void display() override;

    Bill generateBill();
    Bill totalBill();

    void addTreatment(Treatment t);
    int treatmentCount();
    void setWard(Ward *w);

    bool getIsCritical();
    bool getScheduledOperation();
    void scheduleOperation();
};

class StaffMember : public Person
{
protected:
    double salary;
    std::string department;

public:
    StaffMember(std::string n, Date d, int i, std::string c, double sal, std::string dept);
    virtual double calculateBillingRate() = 0;
    virtual void display() override;
};

class GP : public StaffMember
{
public:
    GP(std::string n, Date d, int i, std::string c, double sal, std::string dept);
    double calculateBillingRate() override;
    void display() override;
};

class Surgeon : public StaffMember
{
protected:
    std::string specialisation;

public:
    Surgeon(std::string n, Date d, int i, std::string c, double sal, std::string dept, std::string s);
    double calculateBillingRate() override;
    void display() override;
};

class Nurse : public StaffMember
{
protected:
    Ward *ward;

public:
    Nurse(std::string n, std::string d, int i, std::string c, double sal, std::string dept, double f, Ward *w);
    double calculateBillingRate() override;
    void display() override;
};