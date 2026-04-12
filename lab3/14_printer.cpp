#include <iostream>
#include <stdexcept>
#include <string>
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
    void enqueue(string data)
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
    string dequeue()
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
            string data = temp->data;
            delete temp;
            return data;
        }
        else
        {
            size--;
            Node *temp = front;
            front = front->next;
            string data = temp->data;
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
    string peek()
    {
        if (size == 0)
        {
            return "";
        }
        return front->data;
    }
    void remove(string job)
    {
        Node *temp = front;
        if (size == 0)
        {
            cout << "No items in queue" << endl;
            return;
        }
        if (size == 1 && temp->data == job)
        {
            dequeue();
            cout << "Success! " << endl;
            return;
        }
        if (temp->data == job)
        {
            Node *newTemp = temp->next;
            front = newTemp;
            delete temp;
            size--;
            cout << "Success! " << endl;
            return;
        }
        while (temp->next != nullptr && temp->next->data != job)
        {
            temp = temp->next;
        }

        if (temp->next != nullptr)
        {
            Node *newTemp = temp->next;
            if (newTemp == rear)

                rear = temp;

            temp->next = newTemp->next;

            delete newTemp;
            size--;
            cout << "Success! " << endl;
            return;
        }
        else
            cout << "Not found" << endl;
    }
    bool isEmpty()
    {
        return size == 0;
    }
    ~Queue()
    {
        while (size > 0)
        {
            dequeue();
        }
    }
};

int main()
{
    Queue print;
    print.enqueue("one");
    print.enqueue("two");
    cout << print.peek() << " <- Current data" << endl;
    print.remove("one");
    cout << "is empty: " << print.isEmpty() << endl;
    print.dequeue();
    cout << "is empty: " << print.isEmpty() << endl;
}