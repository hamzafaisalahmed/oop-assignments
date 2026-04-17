#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <stdexcept>
#include "date.h"
#include "treatment.h"
#include "bill.h"
#include "ward.h"
#include "person.h"
#include "hospital.h"
#include "appointment.h"

using namespace std;

// global current date
Date currentDate(15, 4, 2026);

// check function
void check(bool condition, const string &testName)
{
    cout << (condition ? "PASS" : "FAIL") << ": " << testName << endl;
}

int main()
{
    // initializing hospital and patients
    Date dob(1, 1, 1980);
    Date admDate(10, 4, 2026); // 5 days
    GP gp1("Dr. Alvi", dob, 101, "0300-0000001", 50000, "OPD");
    Surgeon surgeon1("Dr. Khan", dob, 102, "0300-0000002", 150000, "Surgery", "Cardiothoracic");
    Nurse nurse1("Nurse Sara", dob, 103, "0300-0000003", 40000, "ICU");
    Patient patient1("Patient Name 1", dob, 501, "0321-1111111", "Cardiac arrest", admDate, true);
    Patient patient2("Patient Name 2", dob, 502, "0321-2222222", "Sprained ankle", admDate, false);

    patient1.addTreatment(Treatment("Oxygen therapy", 2500.0, "Nurse Sara"));
    patient2.addTreatment(Treatment("X-Ray", 1200.0, "Dr. Alvi"));
    GeneralWard bw("Billing Ward", 10);

    bw.admit(patient1);

    vector<Patient *> wardA;
    for (int i = 0; i < 5; i++)
    {
        wardA.push_back(new Patient("patient name " + to_string(i + 1), dob, 100 + i, "random contact no", "disease " + to_string(i + 1), admDate, i % 2 ? true : false));
    }
    vector<Patient *> wardB;
    for (int i = 0; i < 14; i++)
    {
        wardB.push_back(new Patient("patient name " + to_string(i + 1), dob, 200 + i, "random contact no", "disease " + to_string(i + 1), admDate, i % 2 ? true : false));
    }

    Date adm2(5, 4, 2026); // 10 days ago
    Patient *pa = new Patient("A Patient", dob, 801, "...", "Cardiac arrest", adm2, true);
    Patient *pb = new Patient("B Patient", dob, 802, "...", "Broken leg", adm2, false);
    Patient *pc = new Patient("C Patient", dob, 803, "...", "Cardiac arrest", adm2, true);
    Patient *pd = new Patient("D Patient", dob, 804, "...", "Flu", adm2, false);

    pa->addTreatment(Treatment("Surgery", 15000.0, "Dr. Khan"));
    pb->addTreatment(Treatment("Cast", 30000.0, "Dr. Alvi"));
    pc->addTreatment(Treatment("Angiogram", 12000.0, "Dr. Khan"));
    pd->addTreatment(Treatment("Medication", 3000.0, "Nurse Sara"));

    //  TC 01:
    cout << "\n========== TC-01: Polymorphic Display ==========\n";
    vector<Person *> people = {&gp1, &surgeon1, &nurse1, &patient1};
    for (auto *p : people)
        p->display();

    check(true, "TC-01: polymorphic display");

    //=========================================================
    cout << "\n========== TC-02: Billing Operators ==========\n";

    // TC 02

    Bill b1 = patient1.generateBill();
    Bill b2 = patient2.generateBill();

    Bill combined = b1 + b2;
    assert(combined.total() == b1.total() + b2.total());
    assert(!(b1 == b2));
    check(combined.total() == b1.total() + b2.total(), "TC-02: + works");
    check(!(b1 == b2), "TC-02: == works");

    Bill b3 = b1;
    assert(b1 == b3);
    check(b1 == b3, "TC-02: operator== (copy is equal)");

    cout << "Combined bill: " << combined << endl;

    // =========================================================================
    cout << "\n========== TC-03: Ward Comparison ==========\n";
    // TC 03
    GeneralWard w1("Ward A", 20); // 20 beds, 5 patients
    for (int i = 0; i < 5; i++)
        w1.admit(*wardA[i]);

    ICU w2("ICU", 8); // 8 beds, 7 patients
    for (int i = 0; i < 14; i++)
        w2.admit(*wardB[i]); // 7 should be critical so they should be admitted

    check(w1 < w2, "TC-03: w1 < w2 (25% < 87.5%)");
    assert(w1 < w2);

    check(w2 > w1, "TC-03: w2 > w1");
    assert(w2 > w1);

    check(!(w1 == w2), "TC-03: w1 != w2");
    assert(!(w1 == w2));

    // memory management
    for (Patient *p : wardA)
    {
        delete p;
    }
    wardA.clear();
    for (Patient *p : wardB)
    {
        delete p;
    }
    wardB.clear();

    // =========================================================================
    cout << "\n========== TC-04: Ward Admission Rules ==========\n";

    // TC-04
    Patient critical("Patient Name 1", dob, 501, "0321-1111111", "Cardiac arrest", admDate, true);
    Patient routine("Patient Name 2", dob, 502, "0321-2222222", "Sprained ankle", admDate, false);

    ICU icu("ICU", 10);
    assert(icu.admit(critical) == true);
    check(icu.admit(critical) == true, "TC-04: ICU admits critical patient");

    assert(icu.admit(routine) == false);
    check(icu.admit(routine) == false, "TC-04: ICU rejects non-critical patient");

    GeneralWard gw("Ward A", 30);
    assert(gw.admit(routine) == true);
    check(gw.admit(routine) == true, "TC-04: GeneralWard accepts anyone");

    // =========================================================================
    cout << "\n========== TC-05: Double-Booking Prevention ==========\n";

    // TC 05
    AppointmentBook book;
    book.add(Appointment(patient1, gp1, "2026-04-10", "10:00"));

    bool result = book.add(Appointment(patient2, gp1, "2026-04-10", "10:00"));
    assert(result == false);
    check(result == false, "Same doctor , same date , same slot -> rejected");

    bool ok = book.add(Appointment(patient2, gp1, "2026-04-10", "11:00"));
    assert(ok == true);
    check(ok == true, "Different slot -> accepted");
    // =========================================================================
    cout << "\n========== TC-06: Copy Independence ==========\n";
    // TC 06

    Patient original("Hamid Raza", dob, 505, "...", "Fever", admDate, false);
    original.addTreatment(Treatment("Blood test", 500, "Dr. Alvi"));

    Patient copy = original; // copy constructor
    copy.addTreatment(Treatment("MRI", 8000.0, "Dr. Khan"));

    assert(original.treatmentCount() == 1);
    check(original.treatmentCount() == 1, "TC-06: original still has 1 treatment");

    assert(copy.treatmentCount() == 2);
    check(copy.treatmentCount() == 2, "TC-06: copy has 2 treatments");

    // =========================================================================
    cout << "\n========== TC-07: Move Semantics / Discharge ==========\n";
    // TC 07

    Hospital h;

    // initialize hospital object
    h.addWard(new GeneralWard("Test ward", 10));
    // continue

    h.admit(patient1);
    h.discharge(patient1.getId());

    assert(h.isAdmitted(patient1.getId()) == false);
    check(h.isAdmitted(patient1.getId()) == false, "TC-07: patient is no longer admitted");
    assert(h.isArchived(patient1.getId()) == true);
    check(h.isArchived(patient1.getId()) == true, "TC-07: patient is archived");

    // =========================================================================
    cout << "\n========== TC-08: Lambda Filtering & Sorting ==========\n";

    // TC 08

    // initialize hospital with patients
    h.removeWard("Test ward");
    h.addWard(new ICU("ICU", 10));
    h.addWard(new GeneralWard("Ward B", 2)); // making sure icu is first, as hospital's admit searches for first available ward
    h.admit(*pa);
    h.admit(*pb);
    h.admit(*pc);
    h.admit(*pd);
    // continue

    auto criticalInICU = h.filterPatients(
        [](const Patient &p)
        {
            return p.getIsCritical() && p.getWard() == "ICU";
        });
    assert(criticalInICU.size() == 2); // 2 is expected
    check(criticalInICU.size() == 2, "TC-08: filter critical ICU patients");

    auto byBill = h.sortPatients(
        [](const Patient *a, const Patient *b)
        {
            return a->totalBill() < b->totalBill();
        });

    for (int i = 0; i < byBill.size() - 1; i++)
    {
        assert(byBill[i]->totalBill() <= byBill[i + 1]->totalBill());
    }
    check(true, "TC 08: patients sorted");

    // =========================================================================
    cout << "\n========== TC-09: Billing Rate Polymorphism ==========\n";
    // TC 09
    vector<StaffMember *> staffList = {&gp1, &surgeon1, &nurse1};
    for (auto *s : staffList)
    {
        cout << s->getName() << ": PKR " << s->calculateBillingRate() << endl;
    }

    // =========================================================================
    cout << "\n========== TC-10: Ward Revenue ==========\n";
    // TC 10
    // add the 3 patients and Ward A
    h.addWard(new GeneralWard("Ward A", 10));
    Patient *p1 = new Patient("Patient 1", dob, 1000, "...", "Broken leg", currentDate, false);
    Patient *p2 = new Patient("Patient 2", dob, 1001, "...", "Cardiac arrest", currentDate, false);
    Patient *p3 = new Patient("Patient 3", dob, 1002, "...", "Flu", currentDate, false);
    p1->addTreatment(Treatment(" Blood test ", 10000 - 500, "Dr. Alvi "));
    p2->addTreatment(Treatment(" Blood test ", 15000 - 500, "Dr. Alvi "));
    p3->addTreatment(Treatment(" Blood test ", 8000 - 500, "Dr. Alvi "));

    // now admit the 3 patients
    h.admit(*p1);
    h.admit(*p2);
    h.admit(*p3);

    // initialize by discharging all the patients
    h.discharge(pa->getId());
    h.discharge(pb->getId());
    h.discharge(pc->getId());
    h.discharge(pd->getId());
    cout << h.discharge(p1->getId());
    cout << " " << h.discharge(p2->getId());
    cout << " " << h.discharge(p3->getId());
    // continue

    double revenue = h.wardRevenue("Ward A");
    cout << "Ward A revenue: PKR " << revenue << endl;

    check(revenue == 33000.0, "TC-10: ward revenue equals 33000");
    assert(revenue == 33000.0);

    cout << "\n========== All test cases complete ==========\n";
    return 0;
}