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
public:
    Node *top;
    int size;

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
Stack UNDO;
Stack REDO;
void doAction(string action)
{
    UNDO.push(action);
    REDO.clear();
}
bool canUndo()
{
    if (UNDO.size == 0)
        return false;
    else
        return true;
}
bool canRedo()
{
    return !(REDO.size == 0);
}
void undo()
{
    if (canUndo())
        REDO.push(UNDO.pop());
}
void redo()
{
    if (canRedo())
        UNDO.push(REDO.pop());
}

void clearAll()
{
    REDO.clear();
    UNDO.clear();
}
int main()
{

    doAction("one");
    doAction("two");
    doAction("three");

    cout << "initial----------" << endl;
    cout << "Undo Stack: ";
    UNDO.Display();
    cout << "Redo Stack: ";
    REDO.Display();

    cout << "\n---UNDO--------" << endl;
    undo();
    cout << "Undo Stack: ";
    UNDO.Display();
    cout << "Redo Stack: ";
    REDO.Display();

    cout << "\n---more undo---" << endl;
    undo();
    cout << "Undo Stack: ";
    UNDO.Display();
    cout << "Redo Stack: ";
    REDO.Display();

    cout << "\n---REDO----------" << endl;
    redo();
    cout << "Undo Stack: ";
    UNDO.Display();
    cout << "Redo Stack: ";
    REDO.Display();

    return 0;
}