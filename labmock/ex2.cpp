#include <iostream>
#include <stdexcept>
using namespace std;

struct Node
{
    int value;
    Node *next;
    Node(int value) : value(value), next(nullptr) {}
};

class SinglyLinkedList
{
private:
    Node *head;

public:
    SinglyLinkedList() : head(nullptr) {}
    SinglyLinkedList(Node *head) : head(head) {}
    void pushFront(int value)
    {
        Node *newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }
    int popFront()
    {
        if (head == nullptr)
            throw std::out_of_range("List is empty");
        Node *temp = head;
        int tempval = head->value;
        head = head->next;
        delete temp;
        return tempval;
    }
    void insertAt(int value, int index)
    {
        if (index == 0)
        {
            pushFront(value);
            return;
        }
        Node *newNode = new Node(value);
        Node *current = head;
        for (int i = 0; i < index - 1 && current != nullptr; i++)
        {
            current = current->next;
        }
        if (current == nullptr)
        {
            delete newNode;
            throw invalid_argument("Index out of bounds");
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    Node *getHead() const
    {
        return head;
    }
    void display() const
    {
        Node *current = head;
        while (current != nullptr)
        {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }
};

Node *reorderOddEven(Node *head)
{
    if (head == nullptr || head->next == nullptr)
        return nullptr;
    Node *curr = head->next;
    Node *oddCurr = nullptr;
    Node *oddHead = nullptr;
    Node *evenHead = head;
    Node *evenCurr = head;
    int c = 0;
    while (curr != nullptr)
    {
        if (c == 0)
        {
            c++;
            continue;
        }
        if (c % 2 == 0)
        {
            evenCurr->next = curr;
            evenCurr = evenCurr->next;
        }
        else
        {
            if (!oddCurr)
                oddCurr = oddHead = curr;
            else
            {
                oddCurr->next = curr;
                oddCurr = oddCurr->next;
            }
        }
        curr = curr->next;
        c++;
    }
    if (oddCurr)
        oddCurr->next = evenHead;
    evenCurr->next = nullptr;
    return oddHead;
}

int main()
{
    SinglyLinkedList l;
    for (int i = 10; i <= 50; i += 10)
    {
        l.pushFront(i);
    }
    cout << "Original list: " << endl;
    l.display();
    Node *newHead = reorderOddEven(l.getHead());
    cout << "Reordered list: " << endl;
    SinglyLinkedList reordered(newHead);
    reordered.display();
}