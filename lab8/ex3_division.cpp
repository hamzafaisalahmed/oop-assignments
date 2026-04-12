#include <iostream>
#include <stdexcept>
using namespace std;

class DivisionByZeroException : public runtime_error
{
public:
    DivisionByZeroException() : runtime_error("Division by zero is not allowed.") {}
};
double divide()
{
    double x, y;

    while (true)
    {
        try
        {
            cout << "Enter numerator: ";
            if (!(cin >> x))
            {
                cout << "Invalid numerator. Please enter valid numbers." << endl;
                cin.clear();
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
            cout << "Enter denominator: ";
            if (!(cin >> y))
            {
                cout << "Invalid denominator. Please enter valid numbers." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
            if (y == 0)
            {
                throw DivisionByZeroException();
            }
            if (y < 0)
            {
                cout << "Warning: converting negative denominator to positive." << endl;
                y = -y;
            }
        }
        catch (const DivisionByZeroException &e)
        {
            cout << "Error: " << e.what() << "\n";
            continue;
        }
        return x / y;
    }
}

int main()
{
    cout << divide();
}