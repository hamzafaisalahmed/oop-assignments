#include <iostream>
#include <string>
using namespace std;


class Date{
    private:
    int day;
    int month;
    int year;
    public:
    int getDay() {return day;}
    int getMonth() {return month;}
    int getYear() {return year;}
    void setDay(int x) {day = x;}
    void setMonth(int x) {if (x > 12 || x< 1) month = 1; else month = x;}
    void setYear(int x) {year = x;}
    
    string formatDate(){
        string temp = "";
        temp = temp + to_string(day) + '/' + to_string(month) + '/' + to_string(year);
        return temp;
    }
    Date(int x, int y, int z){
        day = x;
        month = y;
        year = z;
        if (y > 12 || y < 1) month = 1;
    }
};



int main() {
Date d1(19, 1, 2024);
cout << d1.formatDate() << endl; // should print 19/1/2024
d1.setDay(17);
cout << d1.formatDate() << endl; // should print 17/1/2024
d1.setMonth(5);
cout << d1.formatDate() << endl; // should print 17/5/2024
Date d2(29, 13, 2024); // should set month to 1
cout << d2.formatDate() << endl; // should print 29/1/2024
return 0;
}


