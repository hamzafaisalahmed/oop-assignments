#include <iostream>

using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node(int data)
    {
        this->data = data;
        next = nullptr;
    }
};

class Queue
{
    Node *front;
    Node *rear;
    int size;

public:
    Queue()
    {
        front = nullptr;
        rear = nullptr;
        size = 0;
    }
    void enqueue(int d)
    {
        Node *temp = new Node(d);
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
    int dequeue()
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
            int data = temp->data;
            delete temp;
            return data;
        }
        else
        {
            size--;
            Node *temp = front;
            front = front->next;
            int data = temp->data;
            delete temp;
            return data;
        }
    }
    void moveNthFront(int n)
    {
        if (size == 0 || size == 1 || n == 1)
            return;
        Node *temp = front;
        Node *prev = nullptr;
        for (int i = 1; i < n; i++)
        {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        temp->next = front;
        front = temp;
        if (temp == rear)
        {
            rear = prev;
            rear->next = nullptr;
        }
        return;
    }
};

int main()
{
    Queue q;

    int vals[] = {5, 11, 34, 67, 43, 55};
    cout << "Original order: ";
    for (int v : vals)
    {
        q.enqueue(v);
        cout << v << " ";
    }

    cout << "\nmove 6" << endl;

    q.moveNthFront(6);

    for (int i = 0; i < 6; i++)
    {
        cout << q.dequeue() << " ";
    }

    return 0;
}