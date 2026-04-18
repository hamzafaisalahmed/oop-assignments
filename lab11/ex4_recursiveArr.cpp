#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

int maxVal(const vector<int> &arr, int i = 0)
{
    if (arr.size() == 0)
        throw runtime_error("Array is empty");
    if (i >= arr.size() - 1)
        return arr[i];
    int max = maxVal(arr, i + 1);
    if (max < arr[i])
        max = arr[i];
    return max;
}

bool isSorted(const vector<int> &arr, int i = 0)
{
    if (arr.size() == 0)
        throw runtime_error("Array is empty");
    if (i >= arr.size() - 1)
        return true;
    if (arr[i] <= arr[i + 1])
        return isSorted(arr, i + 1);
    else
        return false;
}

void printReverse(const vector<int> &arr, int i)
{
    if (arr.size() == 0)
        throw runtime_error("Array is empty");
    if (i >= arr.size() - 1)
    {
        cout << arr[i] << " ";
        return;
    }
    printReverse(arr, i + 1);
    cout << arr[i] << " ";
}

int countEvens(const vector<int> &arr, int i = 0)
{
    if (arr.size() == 0)
        throw runtime_error("Array is empty");
    if (i == arr.size() - 1)
    {
        if (arr[i] % 2 == 0)
            return 1;
        else
            return 0;
    }
    if (arr[i] % 2 == 0)
        return countEvens(arr, i + 1) + 1;
    else
        return countEvens(arr, i + 1);
}
int main()
{
    vector<int> v{3, 7, 1, 9, 4, 6, 2};
    cout << maxVal(v);
    cout << boolalpha << endl
         << isSorted(v) << endl;

    printReverse(v, 0);

    cout << endl
         << countEvens(v);
}