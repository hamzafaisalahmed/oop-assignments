#pragma once
#include <string>
#include "person.h"
#include "date.h"

struct Appointment
{
    Patient *patient;
    StaffMember *doctor;
    Date date;
    std::string time;
    Appointment(Patient &p, StaffMember &e, std::string d, std::string t) : patient(&p), doctor(&e), time(t)
    {
        date = Date(d);
    }
    bool operator==(const Appointment &other) const;
};

class AppointmentBook
{
protected:
    std::vector<Appointment> appointments;
    std::vector<Appointment> completedAppointments;

public:
    bool add(const Appointment &app);
    std::vector<Appointment> getAppointmentByStaff(StaffMember *s, Date d) const;
    std::vector<Appointment> getAppointmentByPatient(Patient *p) const;
    bool cancel(const Appointment &a);
    void completedAppointment(const Appointment &a);
    ~AppointmentBook();
};