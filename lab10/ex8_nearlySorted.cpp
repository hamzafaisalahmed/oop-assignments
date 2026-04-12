#include <random>
#include <iostream>
#include <vector>

using namespace std;

int SelectionSort(vector<int> &arr)
{
    int cmp = 0;
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
            swap(arr[i], arr[min]);
        }
    }
    return cmp;
}

int InsertionSort(vector<int> &arr)
{
    int cmp = 0;
    int size = arr.size();
    for (int i = 1; i < size; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && ++cmp && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
    return cmp;
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
    int n = 1000;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, n - 1);
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        v[i] = i;
    }
    vector<int> k = {0, 5, 10, 50, 100, 500};
    cout << "k\tInsertion sort comparisons\tSelection sort comparisons" << endl;
    vector<int> Icmp;
    vector<int> Scmp;
    for (int i : k)
    {
        vector<int> temp = v;
        for (int j = 0; j < i; j++)
        {
            swap(temp[dis(gen)], temp[dis(gen)]);
        }
        vector<int> temp2 = temp;
        cout << i << "\t" << InsertionSort(temp) << "\t\t\t\t" << SelectionSort(temp2) << endl;
    }
}

// insertion sort starts with O(n) complexity and that increases as the data becomes more unsorted, which causes it to go upto O(n^2) for its worst case