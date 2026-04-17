#include <iostream>
#include <vector>
#include <algorithm>
#include "hospital.h"
#include "person.h"
#include "ward.h"
#include "bill.h"
using namespace std;

void Hospital::admit(Patient &p)
{
    // check if already exists
    for (const auto &x : activePatients)
    {
        if (x->getId() == p.getId())
            return;
    }
    for (const auto &x : archive)
    {
        if (x->getId() == p.getId())
        {
            p.discharge(false);
            activePatients.push_back(&p);
            archive.erase(remove(archive.begin(), archive.end(), x), archive.end());
            return;
        }
    }
    for (const auto &x : wards)
    {
        if (x->admit(p))
        {
            activePatients.push_back(&p);
            return;
        }
    }
}

Bill Hospital::discharge(int id)
{
    for (auto &p : activePatients)
    {
        if (id == p->getId())
        {
            for (auto &x : wards)
            {
                if (x->discharge(p))
                {
                    archive.push_back(p);
                    p->discharge(true);
                    activePatients.erase(remove(activePatients.begin(), activePatients.end(), p), activePatients.end());
                    break;
                }
            }
            return p->generateBill();
        }
    }
    throw invalid_argument("Patient not admitted");
}

bool Hospital::isAdmitted(int id) const
{
    for (const auto &x : activePatients)
    {
        if (x->getId() == id && !x->discharged())
            return true;
    }
    return false;
}

void Hospital::editPatientinWard(Patient *p, bool admit)
{
    if (admit)
        activePatients.push_back(p);
    else
        activePatients.erase(remove(activePatients.begin(), activePatients.end(), p), activePatients.end());
}

bool Hospital::isArchived(int id) const
{
    for (const auto &x : archive)
    {
        if (x->getId() == id && x->discharged())
            return true;
    }
    return false;
}

double Hospital::wardRevenue(string wardName) const
{
    for (const auto &w : wards)
    {
        if (w && w->getName() == wardName)
        {
            double revenue = 0;
            for (const auto &p : archive)
            {
                if (p->getWard() == wardName)
                {
                    revenue += p->totalBill();
                }
            }
            return revenue;
        }
    }
    return 0;
}

vector<Patient *> Hospital::getPatientsByStaff(StaffMember *s) const
{
    vector<Patient *> temp;
    for (const auto &x : activePatients)
    {
        if (x->getPatientsByStaff(s))
            temp.push_back(x);
    }
    for (const auto &x : archive)
    {
        if (x->getPatientsByStaff(s))
            temp.push_back(x);
    }
    return temp;
}

void Hospital::addWard(Ward *w)
{
    wards.push_back(w);
}
void Hospital::addStaff(StaffMember *s)
{
    staff.push_back(s);
}
void Hospital::removeWard(Ward *w)
{
    try
    {
        wards.erase(remove(wards.begin(), wards.end(), w), wards.end());
    }
    catch (...)
    {
        cout << "Ward not found" << endl;
    }
}

void Hospital::removeWard(std::string name)
{
    Ward *temp;
    for (auto &x : wards)
    {
        if (x->getName() == name)
        {
            temp = x;
            wards.erase(remove(wards.begin(), wards.end(), x), wards.end());
            break;
        }
    }
    if (temp)
        delete temp;
    return;
}

Hospital::~Hospital()
{
    for (auto w : wards)

    {
        if (w)
            delete w;
    }
}