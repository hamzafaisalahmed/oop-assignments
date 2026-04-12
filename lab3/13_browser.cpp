#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Node
{
public:
    string data;
    Node *next;
    Node(string data)
    {
        this->data = data;
        this->next = nullptr;
    }
};
class Stack
{
private:
    Node *top;
    int size;

public:
    Stack()
    {
        top = nullptr;
        size = 0;
    }
    Stack(string data)
    {
        Node *temp = new Node(data);
        if (top == nullptr)
            this->top = temp;
        size = 1;
    }
    void Display()
    {
        Node *temp = top;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void push(string data)
    {
        Node *newNode = new Node(data);
        size++;
        if (top == nullptr)
        {
            top = newNode;
        }
        else
        {
            newNode->next = top;
            top = newNode;
        }
    }
    string pop()
    {
        Node *temp = top;
        if (temp == nullptr)
        {
            throw underflow_error("Underflow");
        }
        string data = temp->data;
        top = top->next;
        delete temp;
        size--;
        return data;
    }
    string peek()
    {
        if (top != nullptr)
            return top->data;
        else
            return "";
    }
    bool isEmpty()
    {
        return size == 0;
    }
    void clear()
    {
        while (top != nullptr)
        {
            pop();
        }
    }
    ~Stack()
    {
        while (top != nullptr)
        {
            pop();
        }
    }
};

int main()
{
    Stack history;
    history.push("site1");
    history.push("site2");
    cout << "Current: " << history.peek() << endl;
    cout << "popped: " << history.pop() << endl;
    cout << "is empty: " << history.isEmpty() << endl;
    history.clear();
    cout << "is empty: " << history.isEmpty() << endl;
}