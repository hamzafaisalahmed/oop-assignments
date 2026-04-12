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
        if (size == 0)
        {
            return "";
        }
        return top->data;
    }
    ~Stack()
    {
        while (top != nullptr)
        {
            pop();
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
    string peek()
    {
        if (size == 0)
        {
            return "";
        }
        return front->data;
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
            dequeue();
        }
    }
};
Queue kitchen;
Stack delivery;
void placeOrder(string order)
{
    kitchen.enqueue(order);
    cout << "Order placed!" << endl;
}
void processOrder()
{
    if (kitchen.size != 0)
    {
        delivery.push(kitchen.dequeue());
    }
}
void deliverOrder()
{
    delivery.pop();
}
string getNextKitchenOrder()
{
    return kitchen.peek();
}
string getNextDelivery()
{
    return delivery.peek();
}
int main()
{
    placeOrder("1");
    placeOrder("2");
    cout << "Kitchen: ";
    kitchen.display();
    cout << endl;
    cout << getNextKitchenOrder() << " next order" << endl;
    cout << getNextDelivery() << ": delivery" << endl;
    processOrder();
    cout << "Kitchen: ";
    kitchen.display();
    cout << endl;
    cout << "Delivery: ";
    delivery.Display();
    cout << endl;
    cout << getNextDelivery() << ": delivery" << endl;
    deliverOrder();
    cout << "Delivery: ";
    delivery.Display();
    cout << endl;
}