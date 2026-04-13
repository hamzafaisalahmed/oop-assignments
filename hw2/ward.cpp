#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "ward.h"
#include "person.h"

class Ward
{
protected:
    string name;
    int capacity;
    const double dailyRate;
    vector<Patient *> patients;

public:
    Ward(string n, int cap, double rate) : name(n), capacity(cap), dailyRate(rate)
    {
        if (cap == 0)
            capacity = 1;
    }
    bool operator<(const Ward &other)
    {
        return ((double)patients.size() / capacity) < ((double)other.patients.size() / capacity);
    }
    bool operator>(const Ward &other)
    {
        return ((double)patients.size() / capacity) > ((double)other.patients.size() / capacity);
    }
    bool operator==(const Ward &other)
    {
        return ((double)patients.size() / capacity) == ((double)other.patients.size() / capacity);
    }
    virtual bool admit(Patient *p) = 0;
    bool discharge(Patient *p)
    {
        for (int i = 0; i < patients.size(); i++)
        {
            if (patients[i] == p)
            {
                patients.erase(patients.begin() + i);
                p->setWard(nullptr);
                return true;
            }
        }
        return false;
    }
    double getDailyRate()
    {
        return dailyRate;
    }
    string getName()
    {
        return name;
    }

    virtual ~Ward() {}
};

class GeneralWard : public Ward
{
public:
    GeneralWard(string n, int cap) : Ward(n, cap, 100.0) {}
    bool admit(Patient *p) override
    {
        if (patients.size() < capacity)
        {
            patients.push_back(p);
            p->setWard(this);
            return true;
        }
        return false;
    }
};

class ICU : public Ward
{
public:
    ICU(string n, int cap) : Ward(n, cap, 200.0) {}
    bool admit(Patient *p) override
    {
        if (patients.size() < capacity && p->getIsCritical())
        {
            patients.push_back(p);
            p->setWard(this);
            return true;
        }
        return false;
    }
};

class SurgicalWard : public Ward
{
public:
    SurgicalWard(string n, int cap) : Ward(n, cap, 150.0) {}
    bool admit(Patient *p) override
    {
        if (patients.size() < capacity && p->getScheduledOperation())
        {
            patients.push_back(p);
            p->setWard(this);
            return true;
        }
        return false;
    }
};