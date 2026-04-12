#include <iostream>

using namespace std;

struct Card
{
    int value;
    char suit;
};

void print(Card *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i].value << " " << arr[i].suit << "| ";
    }
    cout << endl;
}

void SelectionSort(Card *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[min].value > arr[j].value)
                min = j;
        }
        if (min != i)
            swap(arr[i], arr[min]);
    }
}

void ShiftSelectionSort(Card *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[min].value > arr[j].value)
                min = j;
        }
        if (min != i)
        {
            Card key = arr[min];
            for (int j = min - 1; j >= i; j--)
            {
                arr[j + 1] = arr[j];
            }
            arr[i] = key;
        }
    }
}

int main()
{
    Card arr[]{{5, 'H'}, {3, 'D'}, {5, 'D'}, {1, 'C'}};
    Card arr2[]{{5, 'H'}, {3, 'D'}, {5, 'D'}, {1, 'C'}};
    print(arr, 4);
    print(arr2, 4);
    SelectionSort(arr, 4);
    print(arr, 4);
    cout << "stable: " << endl;
    ShiftSelectionSort(arr2, 4);
    print(arr2, 4);
}