#include <iostream>
#include <vector>
using namespace std;
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

template <typename T>
void display(const vector<T> &arr)
{
    for (const auto &x : arr)
    {
        cout << x << " ";
    }
    cout << endl;
}

void specialDisplay(const vector<pair<int, string>> &p)
{

    for (auto &x : p)
        cout << "{" << x.first << ", " << x.second << "} ";
    cout << endl;
}
int main()
{
    vector<int> v{38, 27, 43, 3, 9};
    display(v);
    mergeSort(v, 0, v.size() - 1, [](int a, int b)
              { return a > b; }); // desc
    display(v);

    vector<string> v2{"b", "aaaa", "xor", "or"};
    display(v2);
    mergeSort(v2, 0, v2.size() - 1, [](const string &a, const string &b)
              { return a.length() < b.length(); }); // by length
    display(v2);

    vector<pair<int, string>> v3{{3, "three"}, {1, "one"}, {2, "two"}};
    specialDisplay(v3);
    mergeSort(v3, 0, v3.size() - 1, [](const pair<int, string> &a, const pair<int, string> &b)
              { if (a.first != b.first) return a.first < b.first; return a.second < b.second; }); // by first, then by second
    specialDisplay(v3);
}
