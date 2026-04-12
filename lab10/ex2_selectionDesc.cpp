#include <iostream>
#include <vector>
using namespace std;

void SelectionSort(vector<int> &arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int max = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[max] < arr[j])
                max = j;
        }
        if (max != i)
            swap(arr[i], arr[max]);
    }
}
void print(vector<int> &arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int main()
{
    vector<int> v = {3, 6, 1, 8, 2, 9, 4};
    print(v, v.size());
    SelectionSort(v, v.size());
    print(v, v.size());
}