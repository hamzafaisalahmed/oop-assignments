#pragma once
#include <iostream>
#include <string>

using namespace std;

class Date
{
    int day, month, year;

public:
    bool isValidDate(int d, int m, int y)
    {
        if (m < 1 || m > 12 || d < 1)
            return false;
        int maxDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // leap check
        // bool isLeap = false;
        // if (y % 4 == 0)
        // {
        //     if (y % 100 != 0 || y % 400 == 0)
        //     {
        //         isLeap = true;
        //     }
        // }

        // if (m == 2)
        // {
        //     if (isLeap == true)
        //     {
        //         maxDays[1] = 29;
        //     }
        //     else
        //     {
        //         maxDays[1] = 28;
        //     }
        // }

        if (maxDays[m - 1] < d)
            return false;
        return true;
    }
    Date(int d, int m, int y)
    {
        if (isValidDate(d, m, y))
        {
            day = d;
            month = m;
            year = y;
        }
        else
        {
            cout << "Please enter a valid date!" << endl;
            day = 1;
            month = 1;
            year = 2000;
            // setting to default values
        }
    }
    Date()
    {
        day = 1;
        month = 1;
        year = 2000;
    }
    int getDay()
    {
        return day;
    }
    int getMonth()
    {
        return month;
    }
    int getYear()
    {
        return year;
    }
    void displayDate()
    {
        cout << day << "/" << month << "/" << year << endl;
    }
    void setDate(int d, int m, int y)
    {
        if (isValidDate(d, m, y))
        {
            day = d;
            month = m;
            year = y;
        }
        else
        {
            cout << "Please enter a valid date!" << endl;
        }
    }
    // returns the number of days
    friend int calculateDays(Date &curr, Date &other);

    bool operator==(const Date &other) const
    {
        if ((other.day == day) && (other.month == month) && (other.year == year))
            return true;
        else
            return false;
    }
};

int calculateDays(Date &curr, Date &other)
{
    int maxDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int currM = 0;
    int otherM = 0;
    for (int i = 0; i < 12; i++)
    {
        if (i < curr.month - 1)
            currM += maxDays[i];
        if (i < other.month - 1)
            otherM += maxDays[i];
    }
    return (curr.year * 365 + currM + curr.day) - (other.year * 365 + otherM + other.day);
}