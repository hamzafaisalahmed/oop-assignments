#include <iostream>

using namespace std;

template <typename T>
int element_frequency(const T *arr, int size, T val)
{
    int count = 0;
    for (int i = 0; i < size; i++)
        if (arr[i] == val)
            count++;
    return count;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 2, 5, 2};
    int size = sizeof(arr) / sizeof(arr[0]);
    int val = 2;
    cout << "Frequency of " << val << " is: " << element_frequency(arr, size, val) << endl;
}