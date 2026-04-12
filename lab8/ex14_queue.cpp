#include <iostream>

using namespace std;
template <typename T>
class Node
{
public:
    T data;
    Node *next;
    Node(T d)
    {
        data = d;
        next = nullptr;
    }
};
template <typename T>
class Queue
{
    Node<T> *front, *rear;
    int size;

public:
    Queue()
    {
        front = rear = nullptr;
        size = 0;
    }
    void enqueue(T data)
    {
        Node<T> *node = new Node(data);
        if (size == 0)
        {
            front = rear = node;
            size++;
            return;
        }
        rear->next = node;
        rear = node;
        size++;
        return;
    }
    T dequeue()
    {
        if (size == 0)
            throw underflow_error("Queue already empty");
        Node<T> *temp = front;
        if (front == rear)
            front = rear = nullptr;
        else
            front = front->next;
        T data = temp->data;
        delete temp;
        size--;
        return data;
    }
    T Front()
    {
        if (size == 0)
            throw underflow_error("Queue already empty");
        return front->data;
    }
    ~Queue()
    {
        while (size > 0)
            dequeue();
    }
};

int main()
{
    Queue<int> q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    std::cout << "Front element: " << q.Front() << std::endl;

    std::cout << "Dequeued: " << q.dequeue() << std::endl;
    std::cout << "Dequeued: " << q.dequeue() << std::endl;

    std::cout << "New Front: " << q.Front() << std::endl;

    q.dequeue();

    try
    {
        q.dequeue();
    }
    catch (const underflow_error &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}