#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Date
{
    int day, month, year;

public:
    bool isValidDate(int d, int m, int y) const
    {
        if (m < 1 || m > 12 || d < 1)
            return false;
        int maxDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

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
            throw invalid_argument("Please enter a valid date!");
        }
    }

    Date(string dateString)
    {
        int d, m, y;
        y = stoi(dateString.substr(0, 4));
        m = stoi(dateString.substr(5, 2));
        d = stoi(dateString.substr(8, 2));
        if (!isValidDate(d, m, y))
        {
            throw invalid_argument("Please enter a valid date!");
        }
    }

    Date()
    {
        day = 1;
        month = 1;
        year = 2000;
    }
    int getDay() const
    {
        return day;
    }
    int getMonth() const
    {
        return month;
    }
    int getYear() const
    {
        return year;
    }
    void displayDate() const
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
            throw invalid_argument("Please enter a valid date!");
        }
    }
    // returns the number of days
    friend int calculateDays(const Date &curr, const Date &other);

    bool operator==(const Date &other) const
    {
        if ((other.day == day) && (other.month == month) && (other.year == year))
            return true;
        else
            return false;
    }
    ~Date() {}
};

inline int calculateDays(const Date &curr, const Date &other)
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