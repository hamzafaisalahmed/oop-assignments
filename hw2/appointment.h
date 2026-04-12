#include <iostream>
#include <vector>
#include "person.h"
using namespace std;

struct Appointment
{
    Patient *patient;
    Employee *doctor;
    Date date;
    string time;
    Appointment(Patient *p, Employee *e, Date d, string t) : patient(p), doctor(e), date(d), time(t) {}
    bool operator==(const Appointment &other) const
    {
        return (patient == other.patient &&
                doctor == other.doctor &&
                date == other.date &&
                time == other.time);
    }
};

class AppointmentBook
{
protected:
    vector<Appointment> appointments;

public:
    bool add(Appointment &app)
    {
        for (auto x : appointments)
        {
            if ((x.doctor == app.doctor || x.patient == app.patient) && x.date == app.date && x.time == app.time)
                return false;
        }
        appointments.push_back(app);
        return true;
    }
    vector<Appointment> getAppointmentByStaff(Employee *s, Date d)
    {
        vector<Appointment> temp;
        for (auto &x : appointments)
        {
            if (x.doctor == s && x.date == d)
                temp.push_back(x);
        }
        return temp;
    }
    vector<Appointment> getAppointmentByPatient(Patient *p)
    {
        vector<Appointment> temp;
        for (auto &x : appointments)
        {
            if (x.patient == p)
                temp.push_back(x);
        }
        return temp;
    }
    bool cancel(Appointment &a)
    {
        for (int i = 0; i < appointments.size(); i++)
        {
            if (a == appointments[i])
            {
                appointments.erase(appointments.begin() + i);
                return true;
            }
        }
        return false;
    }
    ~AppointmentBook() {}
};