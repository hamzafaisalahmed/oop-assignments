#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student
{
    int scores[5];

public:
    Student()
    {
        for (int i = 0; i < 5; i++)
        {
            scores[i] = 0;
        }
    }
    void input(int a, int b, int c, int d, int e)
    {
        scores[0] = a;
        scores[1] = b;
        scores[2] = c;
        scores[3] = d;
        scores[4] = e;
    }
    int calculateTotalScore()
    {
        int total = 0;
        for (int i = 0; i < 5; i++)
        {
            total += scores[i];
        }
        return total;
    }
};

int main()
{
    vector<Student> Class(5);
    Class[0].input(85, 90, 78, 92, 88);
    Class[1].input(80, 85, 82, 90, 87);
    Class[2].input(78, 82, 80, 88, 85);
    Class[3].input(90, 92, 88, 95, 91);
    Class[4].input(82, 88, 85, 90, 89);
    Student Ali;
    Ali.input(85, 90, 78, 92, 88);
    cout << "Total score of Ali: " << Ali.calculateTotalScore() << endl;
    int max = Ali.calculateTotalScore();
    int count = 0;
    for (int i = 0; i < Class.size(); i++)
    {
        if (Class[i].calculateTotalScore() > Ali.calculateTotalScore())
        {
            count++;
        }
        if (Class[i].calculateTotalScore() > max)
        {
            max = Class[i].calculateTotalScore();
        }
        cout << "Total score of student " << i + 1 << ": " << Class[i].calculateTotalScore() << endl;
    }
    cout << "Number of students with higher total score than Ali: " << count << endl;
    cout << "Highest total score in the class: " << max << endl;
}
