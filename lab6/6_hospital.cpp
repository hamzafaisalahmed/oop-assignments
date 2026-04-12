#include <iostream>
#include <string>

using namespace std;

class HospitalStaff
{
protected:
    int staffID;
    string name;

public:
    HospitalStaff(int s, string n) : staffID(s), name(n) {}
    string getRole()
    {
        return "Hospital Staff";
    }
};

class Doctor : public HospitalStaff
{
private:
    string specialisation;

public:
    Doctor(int s, string n, string sp) : HospitalStaff(s, n), specialisation(sp) {}
    string getRole()
    {
        return "Doctor";
    }
    void prescribe(string patientName)
    {
        cout << "Dr. " << name << " prescribed medication to " << patientName << endl;
    }
};

class Nurse : public HospitalStaff
{
private:
    string ward;

public:
    Nurse(int id, string n, string w) : HospitalStaff(id, n), ward(w) {}
    string getRole()
    {
        return "Nurse";
    }
    void assist(string doctorName)
    {
        cout << "Nurse " << name << " assisted " << doctorName << endl;
    }
};

class Administrator : protected HospitalStaff
{
private:
    string officeLocation;

public:
    Administrator(int id, string n, string o) : HospitalStaff(id, n), officeLocation(o) {}
    void scheduleAppointment()
    {
        cout << "Appointment made" << endl;
    }
};
// getRole cant be used on an administrator because its part of hospitalStaff which is protected
int main()
{
    HospitalStaff s(23, "name1");
    Nurse n(344, "Name2", "medical");
    Doctor d(423, "Name3", "big building");
    cout << "Role: " << n.getRole() << endl;
    cout << "Role: " << d.getRole() << endl;
    n.assist("me");
    d.prescribe("me");
}
