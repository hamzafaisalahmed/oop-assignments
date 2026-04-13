#pragma once
#include <iostream>
#include <vector>

class Patient;
class Ward;
class Bill;

template <typename T, typename func>
class Hospital
{
protected:
    std::vector<Patient *> activePatients;
    std::vector<Patient *> archive;
    std::vector<StaffMember *> staff;

public:
    std::vector<T> filterPatients(func f)
    {
        for (const auto &x :)
    }
};