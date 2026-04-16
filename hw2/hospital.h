#pragma once
#include <vector>
#include <algorithm>
#include <string>
#include "person.h"
#include "ward.h"

class Patient;
class Ward;
class Bill;

class Hospital
{
protected:
    std::vector<Patient *> activePatients;
    std::vector<Patient *> archive;
    std::vector<StaffMember *> staff;
    std::vector<Ward *> wards;

public:
    template <typename func>
    std::vector<Patient *> filterPatients(func f) const
    {
        std::vector<Patient *> temp;
        for (const auto &x : activePatients)
        {
            if (f(*x))
                temp.push_back(x);
        }
        return temp;
    }
    template <typename func>
    std::vector<Patient *> sortPatients(func f) const
    {
        std::vector<Patient *> temp;
        for (const auto &x : activePatients)
        {
            temp.push_back(x);
        }
        std::sort(temp.begin(), temp.end(), f);
        return temp;
    }
    template <typename func>
    std::vector<StaffMember *> filterStaff(func f) const
    {
        std::vector<StaffMember *> temp;
        for (const auto &x : staff)
        {
            if (f(*x))
                temp.push_back(x);
        }
        return temp;
    }
    std::vector<Patient *> getPatientsByStaff(StaffMember *s) const;
    void editPatientinWard(Patient *p, bool admit);
    void admit(Patient &p);
    Bill discharge(Patient &p);
    bool isAdmitted(int id) const;
    bool isArchived(int id) const;
    double wardRevenue(std::string wardName) const;
    void addWard(Ward *w);
    void addStaff(StaffMember *s);
    void removeWard(Ward *w);
    ~Hospital();
};