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

// ── Global current date (15 April 2026) ──────────────────────────────────────
Date currentDate(15, 4, 2026);

// ── Helper ────────────────────────────────────────────────────────────────────
void check(bool condition, const string &testName)
{
    cout << (condition ? "PASS" : "FAIL") << ": " << testName << endl;
}

int main()
{
    Date dob(1, 1, 1980);
    Date admDate(10, 4, 2026); // 5 days
    GP gp1("Dr. Alvi", dob, 101, "0300-0000001", 50000, "OPD");
    Surgeon surgeon1("Dr. Khan", dob, 102, "0300-0000002", 150000, "Surgery", "Cardiothoracic");
    Nurse nurse1("Nurse Sara", dob, 103, "0300-0000003", 40000, "ICU");
    Patient patient1("Patient Name 1", dob, 501, "0321-1111111", "Cardiac arrest", admDate, true);
    Patient patient2("Patient Name 2", dob, 502, "0321-2222222", "Sprained ankle", admDate, false);
    // these are test objects, not stored in any hospital system for now
    //  TC 01:
    cout << "\n========== TC-01: Polymorphic Display ==========\n";
    vector<Person *> people = {&gp1, &surgeon1, &nurse1, &patient1};
    for (auto *p : people)
        p->display();

    check(true, "TC-01: polymorphic display");

    //=========================================================
    cout << "\n========== TC-02: Billing Operators ==========\n";

    patient1.addTreatment(Treatment("Oxygen therapy", 2500.0, "Nurse Sara"));
    patient2.addTreatment(Treatment("X-Ray", 1200.0, "Dr. Alvi"));
    GeneralWard bw("Billing Ward", 10);
    bw.admit(patient1);

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
    Patient critical("Patient Name 1", dob, 501, "0321-1111111", "Cardiac arrest", admDate, true);
    Patient routine("Patient Name 2", dob, 502, "0321-2222222", "Sprained ankle", admDate, false);
    // TC-04
    ICU icu("ICU", 10);
    assert(icu.admit(critical) == true);
    check(icu.admit(critical) == true, "TC-04: ICU admits critical patient");

    assert(icu.admit(routine) == false);
    check(icu.admit(routine) == false, "TC-04: ICU rejects non-critical patient");

    GeneralWard gw("General", 30);
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
    h.admit(patient1);
    h.discharge(patient1.getId());

    assert(h.isAdmitted(patient1.getId()) == false);

    assert(h.isArchived(patient1.getId()) == true);

    // =========================================================================
    cout << "\n========== TC-08: Lambda Filtering & Sorting ==========\n";
    Hospital h2;
    GeneralWard *gw2 = new GeneralWard("Ward B", 50);
    ICU *icu2 = new ICU("ICU-2", 20);
    h2.addWard(gw2);
    h2.addWard(icu2);

    // Create 4 patients with varying criticality and bills
    Date adm2(5, 4, 2026); // 10 days ago
    Patient *pa = new Patient("A Patient", dob, 801, "...", "Cardiac arrest", adm2, true);
    Patient *pb = new Patient("B Patient", dob, 802, "...", "Broken leg", adm2, false);
    Patient *pc = new Patient("C Patient", dob, 803, "...", "Cardiac arrest", adm2, true);
    Patient *pd = new Patient("D Patient", dob, 804, "...", "Flu", adm2, false);

    pa->addTreatment(Treatment("Surgery", 15000.0, "Dr. Khan"));
    pb->addTreatment(Treatment("Cast", 3000.0, "Dr. Alvi"));
    pc->addTreatment(Treatment("Angiogram", 12000.0, "Dr. Khan"));
    pd->addTreatment(Treatment("Medication", 800.0, "Nurse Sara"));

    h2.editPatientinWard(pa, icu2->admit(*pa));
    h2.admit(*pa);
    h2.editPatientinWard(pb, icu2->admit(*pb));
    h2.admit(*pb);
    h2.editPatientinWard(pc, icu2->admit(*pc));
    h2.admit(*pc);
    h2.editPatientinWard(pd, gw2->admit(*pd));
    h2.admit(*pd);
    // TC 08

    // Filter: critical patients in ICU
    auto criticalInICU = h2.filterPatients(
        [](const Patient &p)
        {
            return p.getIsCritical() && p.getWard() == "ICU-2";
        });
    assert(criticalInICU.size() == 2);
    check(criticalInICU.size() == 2, "TC-08: filter critical ICU patients (expect 2)");

    // Filter: by diagnosis keyword
    auto cardiac = h2.filterPatients(
        [](const Patient &p)
        {
            return p.getDiagnosis().find("Cardiac") != string::npos;
        });
    check(cardiac.size() == 2, "TC-08: filter by diagnosis keyword (expect 2)");

    // Sort by total bill ascending
    auto byBill = h2.sortPatients(
        [](Patient *a, Patient *b)
        {
            return a->totalBill() < b->totalBill();
        });
    bool billSorted = true;
    for (int i = 0; i + 1 < (int)byBill.size(); i++)
        if (byBill[i]->totalBill() > byBill[i + 1]->totalBill())
            billSorted = false;
    check(billSorted, "TC-08: sort by bill ascending");

    // Filter staff by department
    h2.addStaff(&gp1);
    h2.addStaff(&surgeon1);
    h2.addStaff(&nurse1);

    auto opdStaff = h2.filterStaff(
        [](const StaffMember &s)
        {
            return s.getDepartment() == "OPD";
        });
    check(opdStaff.size() == 1, "TC-08: filter staff by department (expect 1 OPD)");

    delete pa;
    delete pb;
    delete pc;
    delete pd;

    // =========================================================================
    // TC-09 | Staff billing rate polymorphism
    // =========================================================================
    cout << "\n========== TC-09: Billing Rate Polymorphism ==========\n";

    vector<StaffMember *> staffList = {&gp1, &surgeon1, &nurse1};
    double gpRate = 0, surgeonRate = 0, nurseRate = 0;
    for (auto *s : staffList)
    {
        cout << s->getName() << ": PKR " << s->calculateBillingRate() << endl;
        // collect rates — no typeid/dynamic_cast used
    }
    gpRate = gp1.calculateBillingRate();
    surgeonRate = surgeon1.calculateBillingRate();
    nurseRate = nurse1.calculateBillingRate();

    check(surgeonRate > gpRate, "TC-09: surgeon rate > GP rate");
    check(gpRate > nurseRate, "TC-09: GP rate > nurse rate");
    check(gpRate != surgeonRate && gpRate != nurseRate && surgeonRate != nurseRate,
          "TC-09: all three rates are distinct");

    // =========================================================================
    // TC-10 | Ward revenue report
    // =========================================================================
    cout << "\n========== TC-10: Ward Revenue ==========\n";

    Hospital h3;
    GeneralWard *revWard = new GeneralWard("Ward A", 20);
    h3.addWard(revWard);

    Date admRev(5, 4, 2026); // 10 days before currentDate

    // Create 3 patients with known treatment costs.
    // Ward A daily rate = 100.0, stay = 10 days = 1000 per patient
    // Admin fee = 500 per patient
    // Treatment costs: 8500, 13500, 6500 respectively
    // Expected totals: 8500+1000+500=10000, 13500+1000+500=15000, 6500+1000+500=8000
    // Combined revenue = 33000
    Patient *r1 = new Patient("Rev P1", dob, 901, "...", "Fracture", admRev, false);
    Patient *r2 = new Patient("Rev P2", dob, 902, "...", "Appendix", admRev, false);
    Patient *r3 = new Patient("Rev P3", dob, 903, "...", "Infection", admRev, false);

    r1->addTreatment(Treatment("Cast", 8500.0, "Dr. Alvi"));
    r2->addTreatment(Treatment("Operation", 13500.0, "Dr. Khan"));
    r3->addTreatment(Treatment("IV Drip", 6500.0, "Nurse Sara"));

    revWard->admit(*r1);
    h3.admit(*r1);
    revWard->admit(*r2);
    h3.admit(*r2);
    revWard->admit(*r3);
    h3.admit(*r3);

    h3.discharge(r1->getId());
    h3.discharge(r2->getId());
    h3.discharge(r3->getId());

    double revenue = h3.wardRevenue("Ward A");
    cout << "Ward A revenue: PKR " << revenue << endl;
    check(revenue == 33000.0, "TC-10: ward revenue equals 33000");

    delete r1;
    delete r2;
    delete r3;

    // ── Cleanup TC-07 ────────────────────────────────────────────────────────
    // hWard owned by h — if Hospital destructor frees wards, don't double-delete

    cout << "\n========== All test cases complete ==========\n";
    return 0;
}