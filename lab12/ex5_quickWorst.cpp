#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

int cmp = 0;
random_device rd;
mt19937 gen(rd());

int partition(vector<int> &arr, int l, int h)
{
    int pivot = arr[h];
    int i = l - 1;

    for (int j = l; j < h; j++)
    {
        cmp++;
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
    quickSort(arr, l, pi - 1);
    quickSort(arr, pi + 1, h);
}

int Rpartition(vector<int> &arr, int l, int h)
{
    uniform_int_distribution<> dist(l, h);
    int p = dist(gen);
    swap(arr[h], arr[p]);
    int pivot = arr[h];
    int i = l - 1;

    for (int j = l; j < h; j++)
    {
        cmp++;
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[h]);
    return i + 1;
}

void RquickSort(vector<int> &arr, int l, int h)
{
    if (l >= h)
    {
        return;
    }
    int pi = Rpartition(arr, l, h);
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
    vector<int> v1;
    vector<int> v2;
    for (int i = 0; i < 15; i++)
        v2.push_back(15 - i);
    v1 = v2;
    display(v2);
    quickSort(v2, 0, v2.size() - 1);
    display(v2);
    cout << "Comparisons (last element pivot): " << cmp << endl
         << endl;

    cmp = 0;
    display(v1);
    RquickSort(v1, 0, v2.size() - 1);
    display(v1);
    cout << "Comparisons (random pivot): " << cmp << endl
         << endl;
}

// cmp goes from 105 to 45