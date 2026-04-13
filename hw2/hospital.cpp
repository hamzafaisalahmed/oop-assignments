#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Patient;
class Ward;
class Bill;

template <typename T, typename func>
class Hospital
{
protected:
    vector<Patient *> activePatients;
    vector<Patient *> archive;
    vector<Employee *> staff;
    vector<Ward *> wards;

public:
    vector<Patient *> filterPatients(func f)
    {
        vector<Patient *> temp;
        for (const auto &x : activePatients)
        {
            if (f(*x))
                temp.push_back(x);
        }
        return temp;
    }
    vector<Patient *> sortPatients(func f)
    {
        vector<Patient *> temp;
        for (const auto &x : activePatients)
        {
            temp.push_back(*x);
        }
        sort(temp.begin(), temp.end(), f);
        return temp;
    }
    void admit(Patient &p)
    {
    }
    void discharge(Patient &p)
    {
    }
    bool isAdmitted(int id)
    {
    }
    bool isArchived(int id)
    {
    }
    double wardRevenue(string wardName)
    {
    }

    ~Hospital() {}
};