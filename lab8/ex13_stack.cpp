#include <iostream>

using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node *next;
    Node(T val)
    {
        data = val;
        next = nullptr;
    }
};

template <typename T>
class Stack
{
    Node<T> *tp;
    int size;

public:
    Stack()
    {
        size = 0;
        tp = nullptr;
    }
    T top()
    {
        if (tp)
            return tp->data;
        else
            throw invalid_argument("Stack is empty");
    }
    void push(T val)
    {
        Node<T> *node = new Node(val);
        if (!tp)
        {
            tp = node;
            size++;
        }
        else
        {
            node->next = tp;
            tp = node;
            size++;
        }
    }
    T pop()
    {
        if (!tp)
            throw underflow_error("Stack is already empty");
        size--;
        Node<T> *temp = tp;
        tp = tp->next;
        T data = temp->data;
        delete temp;
        return data;
    }
    ~Stack()
    {
        for (int i = 0; i < size; i++)
        {
            Node<T> *temp = tp;
            tp = tp->next;
            delete temp;
        }
    }
};

int main()
{
    Stack<int> s;
    s.push(10);
    s.push(20);
    cout << "Top: " << s.top() << endl;
    cout << "Popped: " << s.pop() << endl;
    cout << "New Top: " << s.top() << endl;
    return 0;
}