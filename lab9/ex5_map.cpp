#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Student
{
    string name;
    double score;
};

int main()
{
    vector<Student> students;
    int cap = 6;
    for (int i = 0; i < cap; i++)
    {
        Student temp;
        temp.name = "Student no." + to_string(i + 1);
        temp.score = (i * 10) + 40;
        students.push_back(temp);
    }
    vector<char> g(cap);
    transform(students.begin(), students.end(), g.begin(), [](Student s)
              { double score = s.score; if (score >= 80) return 'A';else if(score>= 65) return 'B';else if (score>= 50) return 'C'; else return 'F'; });
    vector<double> scaled(cap);
    transform(students.begin(), students.end(), scaled.begin(), [](Student s)
              {s.score += 5;if (s.score > 100)s.score = 100; return s.score; });
    vector<string> output(cap);
    transform(students.begin(), students.end(), g.begin(), output.begin(), [](Student s, char grade)
              {string temp; temp = s.name + ": " + grade ; return temp; });

    // after scaling
    vector<char> ng(cap);
    transform(scaled.begin(), scaled.end(), ng.begin(), [](double score)
              {  if (score >= 80) return 'A';else if(score>= 65) return 'B';else if (score>= 50) return 'C'; else return 'F'; });

    vector<string> s_output(cap);

    transform(students.begin(), students.end(), ng.begin(), s_output.begin(), [](Student s, char grade)
              {string temp; temp = s.name + ": " + grade ; return temp; });
    for (int i = 0; i < cap; i++)
    {
        cout << "Grade: " << g[i] << endl
             << "Score after bonus: " << scaled[i] << endl
             << "Overall report (without scaling): " << output[i] << endl
             << endl
             << "Overall report (with scaling): " << s_output[i] << endl
             << endl
             << "-----------------------------" << endl;
    }
}
