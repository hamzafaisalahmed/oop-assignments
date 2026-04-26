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
    for (int i = 0; i < 16; i++)
        v1.push_back(i);
    display(v1);
    mergeSort(v1, 0, v1.size() - 1);
    display(v1);
    cout << "Number of comparisons: " << cmp << endl;
    cmp = 0;

    cout << endl;
    vector<int> v2;
    for (int i = 0; i < 16; i++)
        v2.push_back(16 - i);
    display(v2);
    mergeSort(v2, 0, v2.size() - 1);
    display(v2);
    cout << "Number of comparisons: " << cmp << endl;
    cmp = 0;

    cout << endl;

    vector<int> v3;
    for (int i = 0; i < 16; i++)
        v3.push_back((i % 7) + i);
    display(v3);
    mergeSort(v3, 0, v3.size() - 1);
    display(v3);
    cout << "Number of comparisons: " << cmp << endl;
    cmp = 0;
    cout << endl;
}
// number of cmp: 32, 32, 36 respectively
// so nearly identical and fall well below the bound (64)
