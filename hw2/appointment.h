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
    Appointment(Patient *p, StaffMember *e, Date d, std::string t);
    bool operator==(const Appointment &other) const;
};

class AppointmentBook
{
protected:
    std::vector<Appointment> appointments;

public:
    bool add(const Appointment &app);
    std::vector<Appointment> getAppointmentByStaff(StaffMember *s, Date d) const;
    std::vector<Appointment> getAppointmentByPatient(Patient *p) const;
    bool cancel(const Appointment &a);
    ~AppointmentBook();
};