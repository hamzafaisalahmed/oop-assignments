#include <iostream>

using namespace std;

class Date
{
    int month;
    int day;
    int year;

public:
    friend class AgeCalculator;
    Date()
    {
        month = 0;
        day = 0;
        year = 0;
    }
    Date(int m, int d, int y)
    {
        month = m;
        day = d;
        year = y;
    }
    void displayDate()
    {
        cout << month << "/" << day << "/" << year << endl;
    }
};

class AgeCalculator
{
    Date birthDate;
    Date currentDate;

public:
    AgeCalculator(Date bd, Date curr)
    {
        birthDate = bd;
        currentDate = curr;
    }
    void Age()
    {
        int age = currentDate.year - birthDate.year;
        if (currentDate.month < birthDate.month)
            age--;
        else if (currentDate.month == birthDate.month && currentDate.day < birthDate.day)
            age--;
        cout << "Age is " << age << " years. " << endl;
    }
};

int main()
{
    Date today(2, 3, 2026);
    Date bday(3, 21, 2000);
    today.displayDate();
    bday.displayDate();
    AgeCalculator age(bday, today);
    age.Age();
}