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
    vector<Patient> patients;

public:
    bool operator<(const Ward &other)
    {
        return patients.size() < other.patients.size();
    }
    bool operator>(const Ward &other)
    {
        return !(this < other);
    }
};

class GeneralWard : public Ward
{
};

class ICU : public Ward
{
};

class SurgicalWard : public Ward
{
};