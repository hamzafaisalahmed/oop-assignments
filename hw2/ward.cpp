#include <iostream>
#include <string>
#include <vector>
#include "ward.h"
#include "person.h"
#include "appointment.h"

Ward::Ward(string n, int cap, double rate) : name(n), capacity(cap), dailyRate(rate)
{
    if (cap == 0)
        capacity = 1;
}

bool Ward::operator<(const Ward &other) const
{
    return ((double)patients.size() / capacity) < ((double)other.patients.size() / other.capacity);
}

bool Ward::operator>(const Ward &other) const
{
    return ((double)patients.size() / capacity) > ((double)other.patients.size() / other.capacity);
}

bool Ward::operator==(const Ward &other) const
{
    return ((double)patients.size() / capacity) == ((double)other.patients.size() / other.capacity);
}

bool Ward::admit(Patient &p)
{
    // pure virtual
    return false;
}

bool Ward::discharge(Patient *p)
{
    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i] == p)
        {
            patients.erase(patients.begin() + i);
            return true;
        }
    }
    return false;
}

double Ward::getDailyRate() const
{
    return dailyRate;
}

string Ward::getName() const
{
    return name;
}
bool Ward::isAdmitted(Patient *p) const
{
    for (const auto &x : patients)
    {
        if (x == p)
            return true;
    }
    return false;
}

Ward::~Ward() {}

GeneralWard::GeneralWard(string n, int cap) : Ward(n, cap, 100.0) {}

bool GeneralWard::admit(Patient &p)
{
    if (patients.size() < capacity)
    {
        patients.push_back(&p);
        p.setWard(this);
        return true;
    }
    return false;
}

ICU::ICU(string n, int cap) : Ward(n, cap, 200.0) {}

bool ICU::admit(Patient &p)
{
    if (patients.size() < capacity && p.getIsCritical())
    {
        patients.push_back(&p);
        p.setWard(this);
        return true;
    }
    return false;
}

SurgicalWard::SurgicalWard(string n, int cap) : Ward(n, cap, 150.0) {}

bool SurgicalWard::admit(Patient &p)
{
    if (patients.size() < capacity && p.getScheduledOperation())
    {
        patients.push_back(&p);
        p.setWard(this);
        return true;
    }
    return false;
}