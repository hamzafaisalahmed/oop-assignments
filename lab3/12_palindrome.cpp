#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Node
{
public:
    char data;
    Node *next;
    Node(char data)
    {
        this->data = data;
        this->next = nullptr;
    }
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
    LLStack(char data)
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
    void pushCharacter(char data)
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
    char popCharacter()
    {
        Node *temp = top;
        if (temp == nullptr)
        {
            throw underflow_error("Underflow");
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
            popCharacter();
        }
    }
};

class Queue
{
public:
    Node *front;
    Node *rear;
    int size;
    Queue()
    {
        front = nullptr;
        rear = nullptr;
        size = 0;
    }
    void enqueueCharacter(char data)
    {
        Node *temp = new Node(data);
        if (size == 0)
        {
            size++;
            front = temp;
            rear = temp;
            return;
        }
        else
        {
            size++;
            rear->next = temp;
            rear = temp;
            return;
        }
    }
    char dequeueCharacter()
    {
        if (size == 0)
        {
            throw underflow_error("Queue size is already 0");
        }
        else if (size == 1)
        {
            size--;
            front = nullptr;
            Node *temp = rear;
            rear = nullptr;
            char data = temp->data;
            delete temp;
            return data;
        }
        else
        {
            size--;
            Node *temp = front;
            front = front->next;
            char data = temp->data;
            delete temp;
            return data;
        }
    }
    void display()
    {
        Node *temp = front;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    ~Queue()
    {
        while (size > 0)
        {
            dequeueCharacter();
        }
    }
};

int main()
{
    cout << "Enter string: " << endl;
    string word;
    cin >> word;
    LLStack stack;
    Queue queue;
    for (char c : word)
    {
        stack.pushCharacter(tolower(c));
        queue.enqueueCharacter(tolower(c));
    }
    for (int i = 0; i < word.size(); i++)
    {
        if (stack.popCharacter() != queue.dequeueCharacter())
        {
            cout << "Not a palindrome..." << endl;
            return 0;
        }
    }
    cout << "Palindrome" << endl;
    return 0;
}