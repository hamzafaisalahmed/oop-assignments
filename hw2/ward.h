#include <iostream>
#include <string>
#include <vector>
#include "person.h"
using namespace std;

class Ward
{
protected:
    string name;
    int capacity;
    vector<Patient *> patients;

public:
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

    virtual ~Ward() {}
};

class GeneralWard : public Ward
{
public:
    GeneralWard(string n, int cap) : name(n), capacity(cap)
    {
        if (cap == 0)
            capacity = 1;
    }
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
    ICU(string n, int cap) : name(n), capacity(cap)
    {
        if (cap == 0)
            capacity = 1;
    }
    bool admit(Patient *p) override
    {
        if (patients.size() < capacity && p->isCritical)
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
    SurgicalWard(string n, int cap) : name(n), capacity(cap)
    {
        if (cap == 0)
            capacity = 1;
    }
    bool admit(Patient *p) override
    {
        if (patients.size() < capacity && p->scheduledOperation)
        {
            patients.push_back(p);
            p->setWard(this);
            return true;
        }
        return false;
    }
};