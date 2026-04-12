#include <iostream>

using namespace std;

void SelectionSort(int *arr, int size)
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
void print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int main()
{
    int arr[]{29, 10, 14, 37, 13};
    print(arr, 5);
    SelectionSort(arr, 5);
    print(arr, 5);
}