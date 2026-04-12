
#include <iostream>

using namespace std;

struct Node
{
    int data = 0;
    Node *next = nullptr;
};

void reversePrint(Node *head)
{
    if (head == nullptr)
    {
        return;
    }
    reversePrint(head->next);
    cout << head->data << " ";
}

int main()
{

    Node *head = new Node();
    head->data = 1;
    Node *temp = head;
    for (int i = 2; i <= 5; i++)
    {
        temp->next = new Node();
        temp = temp->next;
        temp->data = i;
    }
    cout << "Original list: ";
    temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
    cout << "Reversed list: " << endl;
    reversePrint(head);
}