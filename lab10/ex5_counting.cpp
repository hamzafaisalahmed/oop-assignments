#include <iostream>
#include <vector>

using namespace std;

void SelectionSort(vector<int> &arr)
{
    int cmp = 0;
    int swaps = 0;
    int size = arr.size();
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            cmp++;
            if (arr[min] > arr[j])
                min = j;
        }
        if (min != i)
        {
            swaps++;
            swap(arr[i], arr[min]);
        }
    }
    cout << "Selection sort: " << endl
         << "Comparisons: " << cmp << " Swaps: " << swaps << endl;
}

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
    int n = 15;
    vector<int> sorted;
    vector<int> unsorted;
    vector<int> custom;
    vector<int> sorted2;
    vector<int> unsorted2;
    vector<int> custom2;
    for (int i = 1; i <= n; i++)
    {
        sorted.push_back(i);
        sorted2.push_back(i);
    }
    for (int i = n; i > 0; i--)
    {
        unsorted.push_back(i);
        unsorted2.push_back(i);
    }
    for (int i = 0; i < n; i++)
    {
        custom.push_back((i * 100) % 7 + i);
        custom2.push_back((i * 100) % 7 + i);
    }

    cout << "Sorted: " << endl;
    print(sorted);
    SelectionSort(sorted);
    InsertionSort(sorted2);
    cout << "Results: " << endl;
    print(sorted);
    print(sorted2);
    cout << endl;

    cout << "Unsorted: " << endl;
    print(unsorted);
    SelectionSort(unsorted);
    InsertionSort(unsorted2);
    cout << "Results: " << endl;
    print(unsorted);
    print(unsorted2);
    cout << endl;

    cout << "Custom: " << endl;
    print(custom);
    SelectionSort(custom);
    InsertionSort(custom2);
    cout << "Results: " << endl;
    print(custom);
    print(custom2);
    cout << endl;
}