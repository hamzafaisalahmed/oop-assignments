#include <iostream>
#include <string>
#include <numeric>
using namespace std;

class Rational
{
private:
    int num;
    int denom;

public:
    int get_num() const
    {
        return num;
    }
    int get_den() const { return denom; }
    void set_num(int n) { num = n; }
    void set_den(int d) { denom = d; }

    string to_string() const
    {
        if (denom == 1)
            return std::to_string(num);
        if (num == 0)
            return "0";
        if (denom == 0)
            return "Undefined";
        if (denom < 0)
        {
            int n = -num;
            int d = -denom;
            string temp;
            temp += std::to_string(n);
            temp += "/";
            temp += std::to_string(d);
            return temp;
        }
        string temp;
        temp += std::to_string(num);
        temp += "/";
        temp += std::to_string(denom);
        return temp;
    }

    void reduce()
    {
        int GCD = gcd(num, denom);
        this->num = num / GCD;
        this->denom = denom / GCD;
    }
    Rational operator+(const Rational &r) const
    {
        int n1 = num * r.get_den();
        int n2 = denom * r.get_num();
        int n = n1 + n2;
        int d = denom * r.get_den();
        return Rational(float(n) / float(d));
    }
    Rational operator-(const Rational &r) const
    {
        int n1 = num * r.get_den();
        int n2 = denom * r.get_num();
        int n = n1 - n2;
        int d = denom * r.get_den();
        return Rational(float(n) / float(d));
    }
    Rational operator*(const Rational &r) const
    {
        int n = num * r.get_num();
        int d = denom * r.get_den();
        return Rational(float(n) / float(d));
    }
    Rational operator/(const Rational &r) const
    {
        int n = num * r.get_den();
        int d = denom * r.get_num();
        return Rational(float(n) / float(d));
    }
    bool operator==(const Rational &r) const
    {
        Rational R = r;
        R.reduce();
        if (num == R.get_num() && denom == R.get_den())
            return true;
        else
            return false;
    }
    bool operator!=(const Rational &r) const
    {
        Rational R = r;
        R.reduce();
        if (num == R.get_num() && denom == R.get_den())
            return false;
        else
            return true;
    }

    Rational(string in)
    {
        bool temp = false;
        string num;
        string denom;
        for (int x = 0; x < in.length(); x++)
        {

            if (in[x] == '/')
                temp = true;
            else if (!temp)
                num += in[x];
            else
                denom += in[x];
        }
        this->num = stoi(num);
        this->denom = stoi(denom);
        reduce();
    }
    Rational(float in)
    {
        in = in * 10000;
        int GCD = gcd(10000, int(in));
        this->num = in / GCD;
        this->denom = 10000 / GCD;
        reduce();
    }
};

int main()
{
    Rational r1("9/12");
    cout << "Rational 1: " << r1.to_string() << endl;
    Rational r2(0.5);
    cout << "Rational 2: " << r2.to_string() << endl;
    Rational r3 = r1 + r2;
    cout << "Rational 3: " << r3.to_string() << endl;
    if (r1 != r2)
        cout << "not equal" << endl;
    r1.set_den(4);
    r1.set_num(2);
    r1.reduce();
    if (r1 != r2)
        cout << "not equal" << endl;
    Rational r4 = r1 * r2;
    cout << "Rational 4: " << r4.to_string() << endl;
    Rational r5 = r1 / r2;
    cout << "Rational 5: " << r5.to_string() << endl;
    Rational r6 = r1 - r2;
    cout << "Rational 6: " << r6.to_string() << endl;
    Rational r7("100/300");
    cout << "Rational 7: " << r7.to_string() << endl;
    Rational r8(0.75);
    cout << "Rational 8: " << r8.to_string() << endl;
    Rational r9("1/3");
    if (r7 == r9)
        cout << "equal" << endl;
    return 0;
}