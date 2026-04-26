#include <iostream>
#include <vector>
using namespace std;

struct Student
{
    string name;
    double gpa;
    int year;
};

template <typename T, typename cmp>
void merge(vector<T> &arr, int l, int mid, int r, cmp c)
{
    vector<T> L(arr.begin() + l, arr.begin() + mid + 1);
    vector<T> R(arr.begin() + mid + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < (int)L.size() && j < (int)R.size())
    {
        if (c(L[i], R[j]))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < (int)L.size())
        arr[k++] = L[i++];
    while (j < (int)R.size())
        arr[k++] = R[j++];
}
template <typename T, typename Compare>
void mergeSort(vector<T> &arr, int left, int right, Compare cmp)
{
    if (left >= right)
    {
        return;
    }
    int mid = left + ((right - left) / 2);
    mergeSort(arr, left, mid, cmp);
    mergeSort(arr, mid + 1, right, cmp);
    merge(arr, left, mid, right, cmp);
}
template <typename T, typename Compare>
int partition(vector<T> &arr, int l, int h, Compare cmp)
{
    T pivot = arr[h];
    int i = l - 1;

    for (int j = l; j < h; j++)
    {
        if (cmp(arr[j], pivot))
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[h]);
    return i + 1;
}

template <typename T, typename Compare>
void quickSort(vector<T> &arr, int l, int h, Compare cmp)
{
    if (l >= h)
    {
        return;
    }
    int pi = partition(arr, l, h, cmp);
    quickSort(arr, l, pi - 1, cmp);
    quickSort(arr, pi + 1, h, cmp);
}

template <typename T>
void display(const vector<T> &arr)
{
    for (const auto &x : arr)
    {
        cout << x.name << " " << x.gpa << " " << x.year << endl;
    }
    cout << endl;
}

int main()
{
    vector<Student> students = {
        {"A", 3.5, 2022},
        {"Z", 3.8, 2021},
        {"E", 3.2, 2023},
        {"D", 3.9, 2021},
        {"B", 3.5, 2022}};

    vector<Student> byAlpha = students;
    vector<Student> byYear = students;
    vector<Student> byAlphaQ = students;
    vector<Student> byYearQ = students;
    vector<Student> byGPA = students;

    cout << "Unsorted: " << endl;
    display(students);
    mergeSort(students, 0, students.size() - 1, [](Student &a, Student &b)
              { return a.gpa > b.gpa; });
    cout << "Sorted by GPA (Merge Sort): " << endl;
    display(students);
    quickSort(byGPA, 0, byGPA.size() - 1, [](Student &a, Student &b)
              { return a.gpa > b.gpa; });
    cout << "Sorted by GPA (Quick Sort): " << endl;
    display(byGPA);
    mergeSort(byYear, 0, byYear.size() - 1, [](Student &a, Student &b)
              {if (a.year != b.year)return a.year < b.year; return a.gpa > b.gpa; });
    cout << "Sorted by Year (Merge Sort): " << endl;
    display(byYear);
    quickSort(byYearQ, 0, byYearQ.size() - 1, [](Student &a, Student &b)
              {if (a.year != b.year)return a.year < b.year; return a.gpa > b.gpa; });
    cout << "Sorted by Year (Quick Sort): " << endl;
    display(byYearQ);
    mergeSort(byAlpha, 0, byAlpha.size() - 1, [](Student &a, Student &b)
              { return a.name < b.name; });
    cout << "Sorted by Name (Merge Sort): " << endl;
    display(byAlpha);
    quickSort(byAlphaQ, 0, byAlphaQ.size() - 1, [](Student &a, Student &b)
              { return a.name < b.name; });
    cout << "Sorted by Name (Quick Sort): " << endl;
    display(byAlphaQ);
}
