#include <iostream>
#include <vector>
using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node(int data)
    {
        this->data = data;
        this->next = nullptr;
    }
    friend class LLStack;
};
class LLStack
{
private:
    Node *top;
    int size;

public:
    LLStack()
    {
        top = nullptr;
        size = 0;
    }
    LLStack(int data)
    {
        Node *temp = new Node(data);
        if (top == nullptr)
            this->top = temp;
        size = 1;
    }
    LLStack(LLStack &stack)
    {
        top = nullptr;
        size = 0;
        Node *temp = stack.top;
        vector<int> tempStore;
        while (temp != nullptr)
        {
            tempStore.push_back(temp->data);
            temp = temp->next;
        }
        for (int i = stack.size - 1; i >= 0; i--)
        {
            this->push(tempStore[i]);
        }
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
    void push(int data)
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
    int pop()
    {
        Node *temp = top;
        if (temp == nullptr)
        {
            cout << "Stack underflow" << endl;
            return -1;
        }
        int data = temp->data;
        top = top->next;
        delete temp;
        size--;
        return data;
    }
    ~LLStack()
    {
        while (top != nullptr)
        {
            pop();
        }
    }
};

int main()
{
    LLStack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    cout << "Original stack: ";
    stack.Display();
    LLStack copiedStack(stack);
    cout << "Copied stack: ";
    copiedStack.Display();
    copiedStack.pop();
    copiedStack.pop();
    cout << "Original stack after popping from copied stack: ";
    stack.Display();
    cout << "Copied stack after popping: ";
    copiedStack.Display();
}