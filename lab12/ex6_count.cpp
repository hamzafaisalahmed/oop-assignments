#include <iostream>
#include <vector>
using namespace std;

int cmp = 0;

void merge(vector<int> &arr, int l, int mid, int r)
{
    vector<int> L(arr.begin() + l, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < (int)L.size() && j < (int)R.size())
    {
        cmp++;
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < (int)L.size())
        arr[k++] = L[i++];
    while (j < (int)R.size())
        arr[k++] = R[j++];
}

void mergeSort(vector<int> &arr, int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int mid = l + ((r - l) / 2);
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, r);
    merge(arr, l, mid, r);
}

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
    for (int i = 0; i < 15; i++)
        v1.push_back(i);
    vector<int> V1 = v1;
    display(v1);
    mergeSort(v1, 0, v1.size() - 1);
    display(v1);
    cout << "Number of comparisons (sorted) with merge: " << cmp << endl
         << endl;
    cmp = 0;
    display(V1);
    quickSort(V1, 0, V1.size() - 1);
    display(V1);
    cout << "Number of comparisons (sorted) with quick: " << cmp << endl
         << endl;
    cmp = 0;

    cout << endl;
    vector<int> v2;
    for (int i = 0; i < 15; i++)
        v2.push_back(15 - i);
    vector<int> V2 = v2;
    display(v2);
    mergeSort(v2, 0, v2.size() - 1);
    display(v2);
    cout << "Number of comparisons (reverse) with merge: " << cmp << endl
         << endl;
    cmp = 0;
    display(V2);
    quickSort(V2, 0, V2.size() - 1);
    display(V2);
    cout << "Number of comparisons (reverse) with quick: " << cmp << endl
         << endl;
    cmp = 0;

    cout << endl;

    vector<int> v3;
    for (int i = 0; i < 15; i++)
        v3.push_back((i % 7) + i);
    vector<int> V3 = v3;
    display(v3);
    mergeSort(v3, 0, v3.size() - 1);
    display(v3);
    cout << "Number of comparisons (random) with merge: " << cmp << endl
         << endl;
    cmp = 0;
    display(V3);
    quickSort(V3, 0, V3.size() - 1);
    display(V3);
    cout << "Number of comparisons (random) with quick: " << cmp << endl
         << endl;
    cout << endl;
}

// Input                 Merge Sort comparisons         Quick Sort comparisons
// Sorted (best)        31                              105
// Reversed (worst)     28                              105
// Random (average)     34                              54