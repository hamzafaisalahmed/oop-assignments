#include <iostream>
#include <cmath>
using namespace std;

class Stack
{
    int capacity;
    int top;
    int size;
    int *stack;

public:
    Stack()
    {
        capacity = 10;
        stack = new int[capacity]{};
        top = -1;
        size = 0;
    }
    Stack(int c)
    {
        capacity = c;
        stack = new int[capacity]{};
        top = -1;
        size = 0;
    }
    void push(int val)
    {

        if (size == capacity)
        {
            int *temp = new int[capacity * 2];
            for (int i = 0; i < capacity; i++)
            {
                temp[i] = stack[i];
            }
            delete[] stack;
            stack = temp;
            capacity *= 2;
        }
        size++;
        top++;
        stack[top] = val;
        return;
    }
    int pop()
    {
        if (size == 0)
            throw underflow_error("error");
        else
        {
            size--;
            int temp = stack[top];
            stack[top] = 0;
            top--;
            return temp;
        }
    }
    int peek()
    {
        if (size == 0)
            throw underflow_error("error");
        else
            return stack[top];
    }
    bool isEmpty()
    {
        return size == 0;
    }
    int getSize()
    {
        return size;
    }
    void reverseMiddleHalf()
    {
        int t = round(size / 4.0);
        int left = t;
        int right = size - t - 1;
        while (left < right)
        {
            int temp = stack[right];
            stack[right] = stack[left];
            stack[left] = temp;
            right--;
            left++;
        }
        return;
    }

    string toString()
    {
        string s = "[";

        for (int i = 0; i < size; i++)
        {
            if (i != size - 1)
                s += to_string(stack[i]) + " , ";
            else
                s += to_string(stack[i]) + " ]";
        }
        return s;
    }
    bool operator<(Stack &s)
    {
        if (s.size < size)
            return true;
        else if (s.size == size)
        {
            int sum1 = 0;
            int sum2 = 0;
            for (int i = 0; i < size; i++)
            {
                sum1 += s.stack[i];
                sum2 += stack[i];
            }
            if (sum1 < sum2)
                return true;
            else if (s.stack[top] > stack[top] && sum1 == sum2)
                return true;
        }
        return false;
    }
    ~Stack()
    {
        delete[] stack;
    }
};

int main()
{
    Stack s(10);
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);
    s.push(60);
    s.push(70);
    s.push(80);
    s.push(90);
    s.push(100);
    cout << s.toString() << endl;
    s.reverseMiddleHalf();
    cout << s.toString() << endl;

    Stack s2(10);
    s2.push(10);
    s2.push(20);
    s2.push(30);
    s2.push(40);
    cout << (s < s2) << endl;
}