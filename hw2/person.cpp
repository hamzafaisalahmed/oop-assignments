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

Person::Person(string n, Date d, int i, string c) : name(n), dob(d), id(i), contact(c) {}

void Person::display() const
{
    cout << "Name: " << name << endl;
    cout << "Date of birth: ";
    dob.displayDate();
    cout << "ID: " << id << endl;
    cout << "Contact: " << contact << endl;
}

int Person::getId() const
{
    return id;
}

Person::~Person() {}

Patient::Patient(string n, Date d, int i, string c, string diag, Date adm, bool crit) : Person(n, d, i, c), diagnosis(diag), admission(adm), isDischarged(false), isCritical(crit), scheduledOperation(false), ward(nullptr), staffMembers(nullptr), oldWardRate(0), oldWardName("") {}

void Patient::display() const
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
    cout << endl;
}

double Patient::totalBill() const
{
    double sum = 500;
    int days = calculateDays(currentDate, admission);
    if (ward)
        sum += (ward->getDailyRate() * days);
    else
    {
        sum += (oldWardRate * days);
    }
    for (int i = 0; i < treatments.size(); i++)
    {
        sum += treatments[i].cost;
        if (staffMembers)
        {
            for (const auto &x : *staffMembers)
            {
                if (x->getName() == treatments[i].doctorName)
                {
                    sum += x->calculateBillingRate();
                    break;
                }
            }
        }
    };
    return sum;
}

Bill Patient::generateBill() const
{
    return Bill(this->totalBill());
}

void Patient::addTreatment(const Treatment &t)
{
    treatments.push_back(t);
}
bool Patient::getPatientsByStaff(StaffMember *s) const
{
    for (const auto &t : treatments)
    {
        if (t.doctorName == s->getName())
        {
            return true;
        }
    }
    return false;
}
int Patient::treatmentCount() const
{
    return treatments.size();
}

void Patient::setWard(Ward *w)
{
    ward = w;
}

string Patient::getWard() const
{
    if (ward)
        return ward->getName();
    else if (oldWardName != "")
        return oldWardName;
    else
        return "N/A";
}
bool Patient::getIsCritical() const
{
    return isCritical;
}

bool Patient::getScheduledOperation() const
{
    return scheduledOperation;
}

void Patient::scheduleOperation(bool n)
{
    scheduledOperation = n;
}

void Patient::discharge(bool n)
{
    isDischarged = n;
}

bool Patient::discharged() const
{
    return isDischarged;
}

Patient::Patient(const Patient &other) : Person(other), diagnosis(other.diagnosis), admission(other.admission), ward(other.ward), treatments(other.treatments), isDischarged(other.isDischarged), isCritical(other.isCritical), scheduledOperation(other.scheduledOperation), staffMembers(other.staffMembers), oldWardRate(other.oldWardRate), oldWardName(other.oldWardName) {}

Patient::Patient(Patient &&other) : Person(std::move(other)), diagnosis(std::move(other.diagnosis)), admission(std::move(other.admission)), ward(other.ward), treatments(std::move(other.treatments)), isDischarged(other.isDischarged), isCritical(other.isCritical), scheduledOperation(other.scheduledOperation), staffMembers(other.staffMembers), oldWardRate(other.oldWardRate), oldWardName(other.oldWardName) {}

StaffMember::StaffMember(string n, Date d, int i, string c, double sal, string dept) : Person(n, d, i, c), salary(sal), department(dept) {}

void StaffMember::display() const
{
    Person::display();
    cout << "Salary: Rs." << salary << endl;
    cout << "Department: " << department << endl;
}

GP::GP(string n, Date d, int i, string c, double sal, string dept) : StaffMember(n, d, i, c, sal, dept) {}

double GP::calculateBillingRate() const
{
    return 500;
}

void GP::display() const
{
    StaffMember::display();
    cout << "Hourly consultation fee: " << 500;
    cout << endl
         << endl;
}
void GP::performCheckup(Patient &p) const
{
    cout << "Checkup performed!" << endl;
}

Surgeon::Surgeon(string n, Date d, int i, string c, double sal, string dept, string s) : StaffMember(n, d, i, c, sal, dept), specialisation(s) {}

double Surgeon::calculateBillingRate() const
{
    return 1000;
}

void Surgeon::display() const
{
    StaffMember::display();
    cout << "Per operation fee: " << 1000;
    cout << endl
         << endl;
}
void Surgeon::performSurgery(Patient &p) const
{
    p.scheduleOperation(false);
}
Nurse::Nurse(string n, Date d, int i, string c, double sal, string dept) : StaffMember(n, d, i, c, sal, dept), ward(nullptr) {}

double Nurse::calculateBillingRate() const
{
    return 200;
}

void Nurse::display() const
{
    StaffMember::display();
    cout << "Hourly care fee: " << 200;
    cout << endl
         << endl;
}