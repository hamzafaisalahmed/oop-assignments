#include <iostream>
#include <vector>

using namespace std;

template <typename T, typename BinaryOperation>
vector<vector<T>> matrix_operation(
    const vector<vector<T>> &m1,
    const vector<vector<T>> &m2,
    size_t rows, size_t cols,
    BinaryOperation op)
{
    vector<vector<T>> ans;
    for (int i = 0; i < rows; i++)
    {
        vector<T> temp{};
        for (int j = 0; j < cols; j++)
        {
            temp.push_back(op(m1[i][j], m2[i][j]));
        }
        ans.push_back(temp);
    }
    return ans;
}

int main()
{
    auto add = [](const auto &a, const auto &b)
    { return a + b; };
    vector<vector<int>> mat1 = {{1, 2}, {3, 4}};
    vector<vector<int>> mat2 = {{1, 2}, {3, 4}};
    vector<vector<int>> ans = matrix_operation(mat1, mat2, 2, 2, add);
    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[0].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}