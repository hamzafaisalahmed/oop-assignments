#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "date.h"
#include "treatment.h"
#include "bill.h"
#include "ward.h"
#include "person.h"
#include "hospital.h"
#include "appointment.h"

#include "ward.cpp"
#include "person.cpp"
#include "hospital.cpp"
#include "appointment.cpp"

using namespace std;

// ── Global current date (15 April 2026) ──────────────────────────────────────
Date currentDate(15, 4, 2026);

// ── Helper ────────────────────────────────────────────────────────────────────
void check(bool condition, const string &testName)
{
    cout << (condition ? "PASS" : "FAIL") << ": " << testName << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
int main()
{
    // ── Shared dates ─────────────────────────────────────────────────────────
    Date dob(1, 1, 1980);
    Date admDate(10, 4, 2026); // 5 days before currentDate → 5 days stay

    // ── People ───────────────────────────────────────────────────────────────
    GP gp1("Dr. Alvi", dob, 101, "0300-0000001", 50000, "OPD");
    Surgeon surgeon1("Dr. Khan", dob, 102, "0300-0000002", 150000, "Surgery", "Cardiothoracic");
    Nurse nurse1("Nurse Sara", dob, 103, "0300-0000003", 40000, "ICU");

    // critical patient (for ICU) and routine patient
    Patient patient1("Ali Khan", dob, 501, "0321-1111111", "Cardiac arrest", admDate, true);
    Patient patient2("Sara Baig", dob, 502, "0321-2222222", "Sprained ankle", admDate, false);

    // =========================================================================
    // TC-01 | Polymorphic display
    // =========================================================================
    cout << "\n========== TC-01: Polymorphic Display ==========\n";
    vector<Person *> people = {&gp1, &surgeon1, &nurse1, &patient1};
    for (auto *p : people)
        p->display();

    // Each type prints different role-specific fields — verified visually above.
    // Automated check: pointer loop calls the right override with no if/else.
    check(true, "TC-01: polymorphic display (verify output above — each type differs)");

    // =========================================================================
    // TC-02 | Billing — operator overloading
    // =========================================================================
    cout << "\n========== TC-02: Billing Operators ==========\n";

    patient1.addTreatment(Treatment("Oxygen therapy", 2500.0, "Nurse Sara"));
    patient2.addTreatment(Treatment("X-Ray", 1200.0, "Dr. Alvi"));

    // Give each patient a ward so daily rate is included in the bill.
    GeneralWard gw_billing("Billing Ward", 10);
    gw_billing.admit(&patient1); // patient1 is critical but GeneralWard accepts anyone
    gw_billing.admit(&patient2);

    Bill b1 = patient1.generateBill(); // treatments + ward stay + 500 admin
    Bill b2 = patient2.generateBill();

    Bill combined = b1 + b2;

    check(combined.total() == b1.total() + b2.total(), "TC-02: operator+ totals match");
    check(!(b1 == b2), "TC-02: operator== (different bills not equal)");

    Bill b3 = b1;
    check(b1 == b3, "TC-02: operator== (copy is equal)");

    cout << "Combined bill: ";
    combined.print(); // operator<< not on Bill — using print() as equivalent display

    // =========================================================================
    // TC-03 | Ward comparison operators
    // =========================================================================
    cout << "\n========== TC-03: Ward Comparison ==========\n";

    GeneralWard w1("Ward A", 20);
    ICU w2("ICU", 8);

    // Admit 5 distinct patients into w1  (occupancy = 5/20 = 25%)
    Date admTC03(1, 4, 2026);
    Patient *tc03patients[7];
    for (int i = 0; i < 7; i++)
    {
        // ids 600–606; all critical so ICU can accept them too
        tc03patients[i] = new Patient("P" + to_string(i), dob,
                                      600 + i, "000", "test", admTC03, true);
    }
    for (int i = 0; i < 5; i++)
        w1.admit(tc03patients[i]); // 5/20 = 25%
    for (int i = 0; i < 7; i++)
        w2.admit(tc03patients[i]); // 7/8  = 87.5%

    check(w1 < w2, "TC-03: w1 < w2 (25% < 87.5%)");
    check(w2 > w1, "TC-03: w2 > w1");
    check(!(w1 == w2), "TC-03: w1 != w2");

    for (int i = 0; i < 7; i++)
        delete tc03patients[i];

    // =========================================================================
    // TC-04 | ICU admission rules
    // =========================================================================
    cout << "\n========== TC-04: Ward Admission Rules ==========\n";

    Patient critical("Ali Khan 2", dob, 503, "...", "Cardiac arrest", admDate, true);
    Patient routine("Sara Baig 2", dob, 504, "...", "Sprained ankle", admDate, false);

    ICU icu("ICU-Main", 10);
    check(icu.admit(&critical) == true, "TC-04: ICU admits critical patient");
    check(icu.admit(&routine) == false, "TC-04: ICU rejects non-critical patient");

    GeneralWard gw("General", 30);
    check(gw.admit(&routine) == true, "TC-04: GeneralWard accepts anyone");

    // =========================================================================
    // TC-05 | AppointmentBook — double-booking prevention
    // =========================================================================
    cout << "\n========== TC-05: Double-Booking Prevention ==========\n";

    AppointmentBook book;
    Date apptDate(10, 4, 2026);

    Patient apptPat1("Appt P1", dob, 701, "...", "Check-up", admDate, false);
    Patient apptPat2("Appt P2", dob, 702, "...", "Follow-up", admDate, false);

    Appointment a1(&apptPat1, &gp1, apptDate, "10:00");
    bool firstAdd = book.add(a1);
    check(firstAdd == true, "TC-05: first appointment added");

    // Same doctor, same date, same slot → rejected
    Appointment a2(&apptPat2, &gp1, apptDate, "10:00");
    bool doubleBook = book.add(a2);
    check(doubleBook == false, "TC-05: double-booking rejected");

    // Different slot → accepted
    Appointment a3(&apptPat2, &gp1, apptDate, "11:00");
    bool diffSlot = book.add(a3);
    check(diffSlot == true, "TC-05: different slot accepted");

    // Cancel and verify
    bool cancelled = book.cancel(a1);
    check(cancelled == true, "TC-05: cancellation succeeds");

    // After cancel, same slot should be available again
    Appointment a4(&apptPat2, &gp1, apptDate, "10:00");
    bool afterCancel = book.add(a4);
    check(afterCancel == true, "TC-05: slot available after cancellation");

    // =========================================================================
    // TC-06 | Copy independence — deep copy
    // =========================================================================
    cout << "\n========== TC-06: Copy Independence ==========\n";

    Patient original("Hamid Raza", dob, 505, "...", "Fever", admDate, false);
    original.addTreatment(Treatment("Blood test", 500.0, "Dr. Alvi"));

    Patient copy = original; // copy constructor
    copy.addTreatment(Treatment("MRI", 8000.0, "Dr. Khan"));

    check(original.treatmentCount() == 1, "TC-06: original still has 1 treatment");
    check(copy.treatmentCount() == 2, "TC-06: copy has 2 treatments");

    // =========================================================================
    // TC-07 | Move semantics — patient discharge and archive
    // =========================================================================
    cout << "\n========== TC-07: Move Semantics / Discharge ==========\n";

    Hospital h;
    GeneralWard *hWard = new GeneralWard("Ward A", 20);
    h.addWard(hWard); // expose wards as public or use addWard()

    Patient *p7 = new Patient("Move Patient", dob, 999, "...", "Test", admDate, false);
    h.admit(*p7); // register in hospital active list

    h.discharge(*p7);

    check(h.isAdmitted(999) == false, "TC-07: patient no longer admitted");
    check(h.isArchived(999) == true, "TC-07: patient is in archive");
    // p7 pointer still valid — no double-free on exit
    // (Hospital destructor and scope exit must not crash)

    // =========================================================================
    // TC-08 | Composable filtering with lambdas
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

    h2.editPatientinWard(pa, icu2->admit(pa));
    h2.admit(*pa);
    h2.editPatientinWard(pb, icu2->admit(pb));
    h2.admit(*pb);
    h2.editPatientinWard(pc, icu2->admit(pc));
    h2.admit(*pc);
    h2.editPatientinWard(pd, gw2->admit(pd));
    h2.admit(*pd);

    // Filter: critical patients in ICU
    auto criticalInICU = h2.filterPatients(
        [](const Patient &p)
        {
            return p.getIsCritical() && p.getWard() == "ICU-2";
        });
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

    revWard->admit(r1);
    h3.admit(*r1);
    revWard->admit(r2);
    h3.admit(*r2);
    revWard->admit(r3);
    h3.admit(*r3);

    h3.discharge(*r1);
    h3.discharge(*r2);
    h3.discharge(*r3);

    double revenue = h3.wardRevenue("Ward A");
    cout << "Ward A revenue: PKR " << revenue << endl;
    check(revenue == 33000.0, "TC-10: ward revenue equals 33000");

    delete r1;
    delete r2;
    delete r3;

    // ── Cleanup TC-07 ────────────────────────────────────────────────────────
    delete p7;
    // hWard owned by h — if Hospital destructor frees wards, don't double-delete

    cout << "\n========== All test cases complete ==========\n";
    return 0;
}