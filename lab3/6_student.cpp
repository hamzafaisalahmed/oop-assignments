#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;
uniform_int_distribution<int> dist(30, 100);
random_device rd;
mt19937 gen(rd());

class Student
{
private:
    string name;
    int age;
    string ID;
    string gender;
    vector<vector<int>> marks;
    vector<float> GPA;
    const int creditHr = 3;

    float singleGPA(int marks)
    {
        if (marks >= 85)
            return 4.0;
        else if (marks >= 80)
            return 3.7;
        else if (marks >= 75)
            return 3.3;
        else if (marks >= 70)
            return 3.0;
        else if (marks >= 65)
            return 2.7;
        else if (marks >= 61)
            return 2.3;
        else if (marks >= 58)
            return 2.0;
        else if (marks >= 55)
            return 1.7;
        else if (marks >= 50)
            return 1.0;
        else
            return 0.0;
    }

public:
    const int currentSemester = 1;
    float semesterGPACalculator(int index)
    {
        float total = 0;
        for (int i = 0; i < marks[index].size(); i++)
        {
            total += singleGPA(marks[index][i]) * creditHr;
        }
        GPA[index] = total / (marks[index].size() * creditHr);
        return GPA[index];
    }
    float CGPA()
    {
        float total = 0;
        for (int i = 0; i < GPA.size(); i++)
        {
            semesterGPACalculator(i);
            total += GPA[i];
        }
        return total / 8;
    }

    Student(string n, int a, string id, string g)
    {
        name = n;
        age = a;
        ID = id;
        gender = g;
        for (int i = 0; i < 8; i++)
        {
            marks.push_back(vector<int>());
            GPA.push_back(0);
            for (int j = 0; j < 6; j++)
            {
                if (i == currentSemester - 1)
                {
                    marks[i].push_back(0);
                }
                else
                    marks[i].push_back(dist(gen));
            }
        }
    }
    void inputMarks()
    {
        // only taking input for current semester
        for (int i = 0; i < 6; i++)
        {
            cout << "Enter marks: ";
            int mark;
            cin >> mark;
            marks[currentSemester - 1][i] = mark;
        }
    }
    void report()
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "ID: " << ID << endl;
        cout << "Gender: " << gender << endl;
        cout << "Current semester GPA: " << semesterGPACalculator(currentSemester - 1) << endl;
        cout << "CGPA: " << CGPA() << endl;
    }
};

int main()
{
    Student obj("Hamza faisal", 19, "32406", "Male");
    obj.inputMarks();
    obj.report();
}