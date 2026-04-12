#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void InsertionSort(vector<int> &arr)
{
    int cmp = 0, swaps = 0;
    int size = arr.size();
    for (int i = 1; i < size; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && ++cmp && arr[j] > key)
        {

            swaps++;
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
    cout << "Insertion sort: " << endl
         << "Comparisons: " << cmp << " Swaps: " << swaps << endl;
}

void BinsertionSort(vector<int> &v)
{
    int cmp = 0, swaps = 0;
    int size = v.size();
    for (int i = 1; i < size; i++)
    {
        int key = v[i];

        auto iterator = lower_bound(v.begin(), v.begin() + i, key, [&cmp](int a, int b)
                                    {cmp++;return a<b; });
        auto position = iterator - v.begin();
        int j = i - 1;
        while (j >= position)
        {
            v[j + 1] = v[j];
            swaps++;
            j--;
        }
        v[position] = key;
    }
    cout << "Binary insertion sort: " << endl
         << "Comparisons: " << cmp << " Swaps: " << swaps << endl;
}

void print(vector<int> &arr)
{
    int size = arr.size();
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> arr1;
    vector<int> arr2;
    for (int i = 0; i < 20; i++)
    {
        int val = i * 10 % 7 + i;
        arr1.push_back(val);
        arr2.push_back(val);
    }

    print(arr1);
    print(arr2);

    cout << "After sort:" << endl;
    InsertionSort(arr1);
    BinsertionSort(arr2);

    print(arr1);
    print(arr2);
}

// This is still O(n^2) as even tho the binary search is O(log n), shifting elements still takes O(n), and the shifting also takes O(n), so it remains O(n^2).