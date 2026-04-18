#pragma once
#include <string>
#include <vector>
#include "date.h"
#include "ward.h"
#include "treatment.h"
#include "bill.h"

extern Date currentDate;

class StaffMember;

class Person
{
protected:
    std::string name;
    Date dob;
    int id;
    std::string contact;

public:
    Person(std::string n, Date d, int i, std::string c);
    virtual void display() const;
    int getId() const;
    virtual ~Person();
    std::string getName() const { return name; }
    Date getDob() const { return dob; }
    std::string getContact() const { return contact; }
};

class Patient : public Person
{
protected:
    std::string diagnosis;
    Date admission;
    Ward *ward;
    std::vector<StaffMember *> *staffMembers;
    std::vector<Treatment> treatments;
    bool isDischarged;
    bool isCritical;
    bool scheduledOperation;
    double oldWardRate;
    std::string oldWardName;

public:
    Patient(std::string n, Date d, int i, std::string c, std::string diag, Date adm, bool crit);
    void display() const override;
    double totalBill() const;
    Bill generateBill() const;
    void addTreatment(const Treatment &t);
    int treatmentCount() const;
    bool getPatientsByStaff(StaffMember *s) const;
    void setWard(Ward *w);
    std::string getWard() const;
    bool getIsCritical() const;
    bool getScheduledOperation() const;
    void scheduleOperation(bool n);
    void discharge(bool n);
    bool discharged() const;
    std::string getDiagnosis() const { return diagnosis; }
    void setDiagnosis(std::string diag) { diagnosis = diag; }
    void setCritical(bool crit) { isCritical = crit; }
    Patient(const Patient &other);
    Patient(Patient &&other);
    void updateStaff(std::vector<StaffMember *> *s) { staffMembers = s; }
    void updateWardInfo(double rate, std::string name)
    {
        oldWardRate = rate;
        oldWardName = name;
    }
};

class StaffMember : public Person
{
protected:
    double salary;
    std::string department;

public:
    StaffMember(std::string n, Date d, int i, std::string c, double sal, std::string dept);
    virtual double calculateBillingRate() const = 0;
    virtual void display() const override;
    std::string getDepartment() const { return department; }
};

class GP : public StaffMember
{
public:
    GP(std::string n, Date d, int i, std::string c, double sal, std::string dept);
    double calculateBillingRate() const override;
    void display() const override;
    void performCheckup(Patient &p) const;
};

class Surgeon : public StaffMember
{
protected:
    std::string specialisation;

public:
    Surgeon(std::string n, Date d, int i, std::string c, double sal, std::string dept, std::string s);
    double calculateBillingRate() const override;
    void display() const override;
    void performSurgery(Patient &p) const;
};

class Nurse : public StaffMember
{
protected:
    Ward *ward;

public:
    Nurse(std::string n, Date d, int i, std::string c, double sal, std::string dept);
    double calculateBillingRate() const override;
    void display() const override;
};