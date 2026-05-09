#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sort(vector<int> &v)
{
    int size = v.size();
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

int heightChecker(const std::vector<int> &heights)
{
    vector<int> sorted = heights;
    sort(sorted);
    int c = 0;
    for (int i = 0; i < heights.size(); i++)
    {
        if (heights[i] != sorted[i])
        {
            c++;
        }
    }
    return c;
}

int main()
{
    std::vector<int> h1 = {1, 1, 4, 2, 1, 3};
    std::cout << "Test 1: " << heightChecker(h1)
              << " (expected 3)" << std::endl;
    std::vector<int> h2 = {5, 1, 2, 3, 4};
    std::cout << "Test 2: " << heightChecker(h2)
              << " (expected 5)" << std::endl;
    std::vector<int> h3 = {1, 2, 3, 4, 5};
    std::cout << "Test 3: " << heightChecker(h3)
              << " (expected 0)" << std::endl;
    std::vector<int> h4 = {3, 3, 3, 3};
    std::cout << "Test 4: " << heightChecker(h4)
              << " (expected 0)" << std::endl;
    std::vector<int> h5 = {2, 1};
    std::cout << "Test 5: " << heightChecker(h5)
              << " (expected 2)" << std::endl;
    return 0;
}
