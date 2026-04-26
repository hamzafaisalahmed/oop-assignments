#include <iostream>
#include <vector>
using namespace std;

struct Card
{
    int value;
    char suit;
};

void merge(vector<Card> &arr, int l, int mid, int r)
{
    vector<Card> L(arr.begin() + l, arr.begin() + mid + 1);
    vector<Card> R(arr.begin() + mid + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < (int)L.size() && j < (int)R.size())
    {
        if (L[i].value <= R[j].value)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < (int)L.size())
        arr[k++] = L[i++];
    while (j < (int)R.size())
        arr[k++] = R[j++];
}

void mergeSort(vector<Card> &arr, int l, int r)
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

int partition(vector<Card> &arr, int l, int h)
{
    Card pivot = arr[h];
    int i = l - 1;

    for (int j = l; j < h; j++)
    {
        if (arr[j].value <= pivot.value)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[h]);
    return i + 1;
}

void quickSort(vector<Card> &arr, int l, int h)
{
    if (l >= h)
    {
        return;
    }
    int pi = partition(arr, l, h);
    quickSort(arr, l, pi - 1);
    quickSort(arr, pi + 1, h);
}

void display(const vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void display(const vector<Card> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << "Value: " << arr[i].value << " Suit: " << arr[i].suit << endl;
    }
    cout << endl;
}
int main()
{
    vector<Card> deck1 = {
        {5, 'S'}, {3, 'H'}, {5, 'D'}, {8, 'C'}, {2, 'S'}, {3, 'D'}, {1, 'H'}, {5, 'C'}};
    vector<Card> deck2 = {
        {5, 'S'}, {3, 'H'}, {5, 'D'}, {8, 'C'}, {2, 'S'}, {3, 'D'}, {1, 'H'}, {5, 'C'}};

    cout << "Unsorted: " << endl;
    display(deck1);
    mergeSort(deck1, 0, deck1.size() - 1);

    cout << "Sorted (merge): " << endl;
    display(deck1);

    cout << endl
         << "Unsorted: " << endl;
    display(deck2);
    quickSort(deck2, 0, deck2.size() - 1);
    cout << "Sorted (quick): \n";
    display(deck2);
}
