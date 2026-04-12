#include <iostream>
#include <string>

using namespace std;

class Stack
{
    string data;

public:
    void push(char data)
    {
        this->data += data;
    }
    char pop()
    {
        int size = data.size();
        if (size > 1)
        {
            string newData = data.substr(0, size - 1);
            char temp = data[size - 1];
            data = newData;
            return temp;
        }
        else if (size == 1)
        {
            char temp = data[0];
            data = "";
            return temp;
        }
        else
        {
            throw std::underflow_error("Stack is empty");
        }
    }
    int size()
    {
        return data.size();
    }
};

int main()
{
    cout << "Enter brackets string: ";
    string input;
    Stack stack;
    cin >> input;
    for (char x : input)
    {
        if (x == '[' || x == '(' || x == '{')
            stack.push(x);
        else
        {
            if (stack.size() == 0)
            {
                cout << "false" << endl;
                return 0;
            }
            char temp = stack.pop();
            if ((x == ']' && temp != '[') || (x == ')' && temp != '(') || (x == '}' && temp != '{'))
            {
                cout << "false" << endl;
                return 0;
            }
        }
    }
    if (stack.size() != 0)
    {
        cout << "false" << endl;
        return 0;
    }
    cout << "true" << endl;
}