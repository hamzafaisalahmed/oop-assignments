#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;
template <typename T>
class SparseMatrix
{
    int rows, cols;
    struct node
    {
        int r, c;
        T data;
        node(int row, int col, T d) : r(row), c(col), data(d) {}
    };
    vector<node> data;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c) {}
    void insert(int row, int col, T d)
    {
        if (row < 0 || row >= rows || col < 0 || col >= cols)
        {
            throw invalid_argument("Out of bounds access");
        }
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i].r == row && data[i].c == col)
            {
                data[i].data = d;
                return;
            }
        }
        data.push_back(node(row, col, d));
    }
    T get(int r, int c) const
    {
        for (node d : data)
        {
            if (d.r == r && d.c == c)
            {
                return d.data;
            }
        }
        return T{};
    }

    SparseMatrix operator+(const SparseMatrix &other)
    {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Cannot add matrices: dimensions dont match");
        SparseMatrix ans(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                T temp = this->get(i, j);
                T temp2 = other.get(i, j);
                if (temp + temp2 != T{})
                {
                    ans.insert(i, j, temp + temp2);
                }
            }
        }
        return ans;
    }

    SparseMatrix operator-(const SparseMatrix &other)
    {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Cannot subtract matrices: dimensions dont match");
        SparseMatrix ans(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                T temp = this->get(i, j);
                T temp2 = other.get(i, j);
                if (temp - temp2 != T{})
                {
                    ans.insert(i, j, temp - temp2);
                }
            }
        }
        return ans;
    }

    SparseMatrix operator*(const SparseMatrix &other)
    {
        if (cols != other.rows)
            throw invalid_argument("Cannot multiply matrices: invalid dimensions");
        SparseMatrix ans(rows, other.cols);
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < other.cols; j++)
            {
                T sum = T{};
                for (int k = 0; k < this->cols; k++)
                {
                    sum = sum + (this->get(i, k) * other.get(k, j));
                }
                if (sum != T{})
                    ans.insert(i, j, sum);
            }
        }
        return ans;
    }
    void print()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << get(i, j) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main()
{
    try
    {
        SparseMatrix<int> A(2, 2);
        SparseMatrix<int> B(2, 2);

        A.insert(0, 0, 1);
        A.insert(1, 1, 2);

        B.insert(0, 1, 3);
        B.insert(1, 0, 4);

        A.print();
        B.print();

        SparseMatrix<int> sum = A + B;
        sum.print();

        SparseMatrix<int> diff = A - B;
        diff.print();

        SparseMatrix<int> product = A * B;
        product.print();

        cout << "error now" << endl;
        A.insert(5, 5, 10);
    }
    catch (const invalid_argument &e)
    {
        cout << "Caught expected error: " << e.what() << endl;
    }

    return 0;
}
