#include <iostream>

using namespace std;
template <typename T>
void sort_array(T *arr, int size)
{
    // ascending order
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                T temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
template <typename T>
void print_array(T *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
template <typename T>
void reverse_array(T *arr, int size)
{
    for (int i = 0; i < size / 2; i++)
    {
        T temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}
template <typename T>
int binary_search(T *arr, int lb, int ub, T val)
{
    if (lb > ub)
        return -1;
    int m = (lb + ub) / 2;
    if (val == arr[m])
        return m;
    if (val > arr[m])
        return binary_search(arr, m + 1, ub, val);
    else
        return binary_search(arr, lb, m - 1, val);
}

int main()
{
    int arr[] = {5, 3, 2, 4, 1};
    int size = 5;
    print_array(arr, size);
    reverse_array(arr, size);
    print_array(arr, size);
    cout << endl;
    print_array(arr, size);
    sort_array(arr, size);
    print_array(arr, size);
    cout << endl;
    cout << "index: " << binary_search(arr, 0, 4, 1);
}