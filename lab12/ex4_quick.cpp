#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int partition(vector<int> &arr, int l, int h)
{
    int pivot = arr[h];
    int i = l - 1;

    for (int j = l; j < h; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[h]);
    return i + 1;
}

void quickSort(vector<int> &arr, int l, int h)
{
    if (l >= h)
    {
        return;
    }
    int pi = partition(arr, l, h);
    cout << "Pivot " << arr[pi] << " placed at index " << pi << ": [ ";
    for (int x : arr)
        cout << x << " ";
    cout << "]\n";
    quickSort(arr, l, pi - 1);
    quickSort(arr, pi + 1, h);
}

void display(const vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> v{8, 3, 7, 1, 5, 2, 4};
    display(v);
    quickSort(v, 0, v.size() - 1);
    display(v);
}