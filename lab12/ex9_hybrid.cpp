#include <iostream>
#include <random>
#include <vector>
using namespace std;

int cmp = 0;

void InsertionSort(vector<int> &arr, int lb, int ub)
{
    for (int i = lb; i <= ub; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= lb && ++cmp && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int medianOfThree(vector<int> &arr, int low, int high)
{
    int mid = low + (high - low) / 2;
    // Sort the three candidate values and return the middle index
    if (arr[low] > arr[mid])
        swap(arr[low], arr[mid]);
    if (arr[low] > arr[high])
        swap(arr[low], arr[high]);
    if (arr[mid] > arr[high])
        swap(arr[mid], arr[high]);
    // arr[low] <= arr[mid] <= arr[high]; median is at mid
    swap(arr[mid], arr[high - 1]); // Place median just before high
    return high - 1;
}

int partition(vector<int> &arr, int l, int h)
{
    int pivotIndex = medianOfThree(arr, l, h);
    int pivot = arr[pivotIndex];
    swap(arr[pivotIndex], arr[h]);
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

void print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void sort(vector<int> &arr, int lb, int ub, int k)
{
    int size = ub - lb + 1;
    if (size <= k)
    {
        InsertionSort(arr, lb, ub);
        return;
    }
    else
    {
        int pi = partition(arr, lb, ub);
        sort(arr, lb, pi - 1, k);
        sort(arr, pi + 1, ub, k);
    }
}

int main()
{
    int n[]{50, 200, 1000};
    int k[]{5, 10, 20};
    for (int i : k)
    {
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
            sort(arr, 0, j - 1, i);
            cout << "n: " << j << " k: " << i << " comparisons: " << cmp << endl;
            cmp = 0;
        }
    }
}
// small subarrays benefit from insertion sort because it works faster for small datasets which are present close to each other in memory.
