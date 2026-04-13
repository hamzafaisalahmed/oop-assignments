#pragma once
#include "person.h"
#include <vector>
#include <string>
#include "date.h"

// Forward declarations
class Patient;
class StaffMember;

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
    AppointmentBook() {} // Explicit constructor

    bool add(const Appointment &app);

    std::vector<Appointment> getAppointmentByStaff(StaffMember *s, Date d);
    std::vector<Appointment> getAppointmentByPatient(Patient *p);

    bool cancel(const Appointment &a);

    ~AppointmentBook();
};
