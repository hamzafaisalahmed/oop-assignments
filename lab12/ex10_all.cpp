#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

void merge(vector<int> &arr, int l, int mid, int r)
{
    vector<int> L(arr.begin() + l, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < (int)L.size() && j < (int)R.size())
    {
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

void SelectionSort(vector<int> &arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[min] > arr[j])
                min = j;
        }
        if (min != i)
            swap(arr[i], arr[min]);
    }
}

void InsertionSort(vector<int> &arr, int size)
{
    for (int i = 1; i < size; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
int main()
{
    int n[]{100, 1000, 10000};
    for (int j : n)
    {
        vector<int> arr(j);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, j - 1);
        for (int x = 0; x < j; x++)
        {
            arr[x] = dis(gen);
        }
        vector<int> arr2 = arr;
        vector<int> arr3 = arr;
        vector<int> arr4 = arr;
        auto start = chrono::high_resolution_clock::now();
        mergeSort(arr, 0, arr.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        cout << "n = " << j << endl;
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "Merge Sort - Time: " << duration.count() << " ms" << endl;
        cout << endl;
        auto start2 = chrono::high_resolution_clock::now();
        quickSort(arr2, 0, arr2.size() - 1);
        auto end2 = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2);
        cout << "Quick Sort - Time: " << duration2.count() << " ms" << endl;
        cout << endl;
        auto start3 = chrono::high_resolution_clock::now();
        SelectionSort(arr3, arr3.size());
        auto end3 = chrono::high_resolution_clock::now();
        auto duration3 = chrono::duration_cast<chrono::milliseconds>(end3 - start3);
        cout << "Selection Sort - Time: " << duration3.count() << " ms" << endl;
        cout << endl;
        auto start4 = chrono::high_resolution_clock::now();
        InsertionSort(arr4, arr4.size());
        auto end4 = chrono::high_resolution_clock::now();
        auto duration4 = chrono::duration_cast<chrono::milliseconds>(end4 - start4);
        cout << "Insertion Sort - Time: " << duration4.count() << " ms" << endl;
        cout << endl;
    }
}

// at n = 10000, the O(nlog(n)) advantage is clearly visible
// overall, quick sort > merge sort > insertion sort > selection sort, with the difference becoming more visible as n increased.