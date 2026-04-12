#include <iostream>
#include <random>
using namespace std;

int InsertionSort(int *arr, int lb, int ub)
{
    int cmp = 0;
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
    return cmp;
}

int SelectionSort(int *arr, int lb, int ub)
{
    int min = lb, cmp = 0;
    for (int j = lb + 1; j <= ub; j++)
    {
        cmp++;
        if (arr[min] > arr[j])
            min = j;
    }
    if (min != lb)
        swap(arr[lb], arr[min]);
    return cmp;
}

void print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int sort(int *arr, int lb, int ub, int k, int &cmp)
{
    int size = ub - lb + 1;
    if (size <= k)
    {
        cmp += InsertionSort(arr, lb, ub);
        return cmp;
    }
    else
    {
        cmp += SelectionSort(arr, lb, ub);
        return sort(arr, lb + 1, ub, k, cmp);
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
            int arr[j];
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, j - 1);
            for (int x = 0; x < j; x++)
            {
                arr[x] = dis(gen);
            }
            int cmp = 0;
            sort(arr, 0, j - 1, i, cmp);
            cout << "n: " << j << " k: " << i << " comparisons: " << cmp << endl;
        }
    }
}
// the hybrid sort performed better as k increased, but not by alot as most of the sorting is still done by selection sort for large arrays, which means overall complexity is still O(n^2)
