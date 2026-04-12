#include <iostream>
#include <vector>

using namespace std;

class IntegerSet
{
private:
    vector<bool> set;

public:
    IntegerSet unionOfSet(const IntegerSet &s1, const IntegerSet &s2)
    {
        IntegerSet a;
        for (int i = 0; i < a.set.size(); i++)
        {
            if (s1.set[i] == true || s2.set[i] == true)
            {
                a.set[i] = true;
            }
        }
        return a;
    }
    IntegerSet intersectionOfSets(const IntegerSet &s1, const IntegerSet &s2)
    {
        IntegerSet a;
        for (int i = 0; i < a.set.size(); i++)
        {
            if (s1.set[i] == true && s2.set[i] == true)
            {
                a.set[i] = true;
            }
        }
        return a;
    }
    void insertElement(int k)
    {
        if (k >= 0 && k <= 100)
        {
            set[k] = true;
            cout << "Element inserted" << endl;
            return;
        }
    }
    void deleteElement(int m)
    {
        if (m >= 0 && m <= 100)
        {
            set[m] = false;
            cout << "Element deleted" << endl;
            return;
        }
    }
    string to_string()
    {
        string temp{""};
        for (int i = 0; i < set.size(); i++)
        {
            if (set[i] == true)
            {
                temp += (std::to_string(i) + " ");
            }
        }
        if (temp == "")
            return "{}";
        return temp;
    }
    bool isEqualTo(const IntegerSet &s)
    {
        for (int i = 0; i < set.size(); i++)
        {
            if (s.set[i] != set[i])
                return false;
        }
        return true;
    }

    IntegerSet()
    {
        for (int i = 0; i <= 100; i++)
            set.push_back(false);
    }
    IntegerSet(int *arr, int size)
    {
        for (int i = 0; i <= 100; i++)
            set.push_back(false);
        for (int i = 0; i < size; i++)
        {
            if (arr[i] >= 0 && arr[i] <= 100)
                set[arr[i]] = true;
        }
    }
};

int main()
{
    IntegerSet set1;
    set1.insertElement(5);
    set1.insertElement(10);
    set1.insertElement(15);
    cout << "Set 1: " << set1.to_string() << endl;

    IntegerSet set2;
    set2.insertElement(10);
    set2.insertElement(20);
    set2.insertElement(30);
    cout << "Set 2: " << set2.to_string() << endl;

    IntegerSet unionSet = set1.unionOfSet(set1, set2);
    cout << "Union of Set 1 and Set 2: " << unionSet.to_string() << endl;

    IntegerSet intersectionSet = set1.intersectionOfSets(set1, set2);
    cout << "Intersection of Set 1 and Set 2: " << intersectionSet.to_string() << endl;

    if (set1.isEqualTo(set2))
        cout << "Set 1 is equal to Set 2" << endl;
    else
        cout << "Set 1 is not equal to Set 2" << endl;

    IntegerSet set3;
    cout << "Set 3: " << set3.to_string() << endl;
    cout << "Intersection of Set 1 and Set 3: " << set1.intersectionOfSets(set1, set3).to_string() << endl;
    return 0;
}