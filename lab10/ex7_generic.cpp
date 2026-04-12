#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename T, typename Compare>
void insertionSort(vector<T> &arr, Compare cmp)
{
    for (int i = 1; i < arr.size(); i++)
    {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && cmp(arr[j], key))
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
};

template <typename T>
void print(const vector<T> &arr)
{
    for (const T &x : arr)
        cout << x << " ";
    cout << "\n";
}

int main()
{
    // vectors
    vector<int> nums = {15, 3, 7, 1, 9};
    vector<string> letters = {"d", "A", "b", "C"};
    vector<pair<int, string>> pairs = {{2, "B"}, {1, "Z"}, {2, "A"}};
    // lambdas
    auto asc = [](int a, int b)
    { return a > b; }; // arr[j] > key
    auto alpha = [](string a, string b)
    { return toupper(b[0]) > toupper(a[0]); }; // arr[j] < key
    auto pairCmp = [](pair<int, string> a, pair<int, string> b)
    {
        if (a.first != b.first)
        {
            return a.first > b.first; // arr[j] > key
        }
        return a.second > b.second; // arr[j] > key
    };

    print(nums);
    insertionSort(nums, asc);
    print(nums);

    print(letters);
    insertionSort(letters, alpha);
    print(letters);

    for (auto p : pairs)
        cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;
    insertionSort(pairs, pairCmp);
    for (auto p : pairs)
        cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;
}