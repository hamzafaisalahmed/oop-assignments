#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

struct Student
{
    string name;
    double gpa;
    int year;
};

void SelectionSort(vector<Student> &arr, function<bool(const Student &, const Student &)> cmp)
{
    int size = arr.size();
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (cmp(arr[j], arr[min]))
                min = j;
        }
        if (min != i)
        {
            swap(arr[i], arr[min]);
        }
    }
}

void InsertionSort(vector<Student> &arr, function<bool(const Student &, const Student &)> cmp)
{
    int size = arr.size();
    for (int i = 1; i < size; i++)
    {
        Student key = arr[i];
        int j = i - 1;

        while (j >= 0 && cmp(key, arr[j]))
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}
void print(vector<Student> &arr)
{
    int size = arr.size();
    for (int i = 0; i < size; i++)
    {
        cout << arr[i].name << " " << arr[i].gpa << " " << arr[i].year << endl;
    }
    cout << endl;
}

int main()
{
    vector<Student> original = {
        {"A-name", 3.9, 2024},
        {"B-name", 3.5, 2025},
        {"C-name", 3.9, 2024},
        {"D-name", 3.2, 2023},
        {"E-name", 3.8, 2025}};

    cout << "GPA sort: " << endl;
    vector<Student> task1 = original;
    vector<Student> task1s = original;

    InsertionSort(task1, [](const Student &a, const Student &b)
                  { return a.gpa > b.gpa; });
    SelectionSort(task1s, [](const Student &a, const Student &b)
                  { return a.gpa > b.gpa; });
    cout << "insertion: " << endl;
    print(task1);
    cout << "selection: " << endl;
    print(task1s);
    cout << "===========================" << endl;
    cout << "year then gpa" << endl;
    vector<Student> task2 = original;
    vector<Student> task2s = original;
    InsertionSort(task2, [](const Student &a, const Student &b)
                  {
        if (a.year != b.year) return a.year < b.year;
        return a.gpa > b.gpa; });
    SelectionSort(task2s, [](const Student &a, const Student &b)
                  {
        if (a.year != b.year) return a.year < b.year;
        return a.gpa > b.gpa; });
    cout << "insertion: " << endl;
    print(task2);
    cout << "selection: " << endl;
    print(task2s);
    cout << "===========================" << endl;
    cout << "alphabetic" << endl;
    vector<Student> task3 = original;
    vector<Student> task3s = original;
    InsertionSort(task3, [](const Student &a, const Student &b)
                  { return a.name < b.name; });
    SelectionSort(task3s, [](const Student &a, const Student &b)
                  { return a.name < b.name; });
    cout << "insertion: " << endl;
    print(task3);
    cout << "selection: " << endl;
    print(task3s);
    cout << "===========================" << endl;
}