#pragma once
#include <string>
#include <vector>

class Patient;
class Hospital;

class Ward
{
protected:
    std::string name;
    int capacity;
    const double dailyRate;
    std::vector<Patient *> patients;

public:
    Ward(std::string n, int cap, double rate);
    bool operator<(const Ward &other) const;
    bool operator>(const Ward &other) const;
    bool operator==(const Ward &other) const;
    virtual bool admit(Patient &p) = 0;
    bool discharge(Patient *p);
    double getDailyRate() const;
    std::string getName() const;
    bool isAdmitted(Patient *p) const;
    virtual ~Ward();
};

class GeneralWard : public Ward
{
public:
    GeneralWard(std::string n, int cap);
    bool admit(Patient &p) override;
};

class ICU : public Ward
{
public:
    ICU(std::string n, int cap);
    bool admit(Patient &p) override;
};

class SurgicalWard : public Ward
{
public:
    SurgicalWard(std::string n, int cap);
    bool admit(Patient &p) override;
};