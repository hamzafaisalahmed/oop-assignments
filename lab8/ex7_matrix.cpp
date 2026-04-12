#include <iostream>
#include <stdexcept>

using namespace std;

class matrix
{
    int rows, cols;
    double **arr;

public:
    matrix(int r, int c) : rows(r), cols(c)
    {
        if (r <= 0 || c <= 0)
            throw invalid_argument("Rows and columns must be positive integers.");
        arr = new double *[rows];
        for (int i = 0; i < rows; i++)
        {
            arr[i] = new double[cols]{0};
        }
    }
    double &operator()(int r, int c)
    {
        if (r < 0 || r >= rows || c < 0 || c >= cols)
        {
            throw runtime_error("Out of bounds");
        }
        else
            return arr[r][c];
    }

    void display()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                std::cout << arr[i][j] << " ";
            }
            std::cout << endl;
        }
        std::cout << endl;
    }

    matrix operator+(matrix &other)
    {
        if (other.rows == rows && other.cols == cols)
        {
            matrix sum(rows, cols);
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    sum(i, j) = other(i, j) + (*this)(i, j);
                }
            }
            return sum;
        }
        else
            throw logic_error("Invalid operation: dimensions do not match");
    }

    ~matrix()
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] arr[i];
        }
        delete[] arr;
    }
};

int main()
{
    matrix m1(2, 3);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m1(i, j) = i + j;
        }
    }
    m1.display();
    matrix m2(2, 3);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m2(i, j) = i - j;
        }
    }
    m2.display();
    matrix m3 = m1 + m2;
    m3.display();
    matrix m4(3, 2);
    try
    {
        matrix m5 = m1 + m4;
    }
    catch (const logic_error &e)
    {
        cerr << e.what() << endl;
    }
    try
    {
        m1(3, 5) = 10;
    }
    catch (const runtime_error &e)
    {
        cerr << e.what() << endl;
    }
    try
    {
        matrix m6(-1, 5);
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what() << endl;
    }
}