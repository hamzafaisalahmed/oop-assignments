#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player
{
private:
    int id;
    string name;
    int level;
    string type;
    int arrivalOrder;
    bool withdrawn;

public:
    Player()
    {
        id = 0;
        name = "";
        level = 0;
        type = "";
        arrivalOrder = 0;
        withdrawn = false;
    }
    Player(int id, string name, int level, string type, int arrivalOrder)
    {
        this->id = id;
        this->name = name;
        this->level = level;
        this->type = type;
        this->arrivalOrder = arrivalOrder;
        withdrawn = false;
    }
    int getId() { return id; }
    string getName() { return name; }
    int getLevel() { return level; }
    string getType() { return type; }
    int getArrivalOrder() { return arrivalOrder; }
    void setLevel(int level) { this->level = level; }
    void setWithdraw(bool x) { withdrawn = x; }
    bool isWithdrawn()
    {
        return withdrawn;
    }
    Player(Player const &player)
    {
        id = player.id;
        name = player.name;
        level = player.level;
        type = player.type;
        arrivalOrder = player.arrivalOrder;
        withdrawn = player.withdrawn;
    }
};
// Node for queues-------------------------------------------
class Node
{
public:
    Player *player;
    Node *next;
    Node(Player *player)
    {
        this->player = player;
        this->next = nullptr;
    }
};

class NormalQueue
{
private:
    Node *front;
    Node *rear;
    int size;

public:
    NormalQueue()
    {
        front = nullptr;
        rear = nullptr;
        size = 0;
    }

    void withdraw(bool flag)
    {
        if (flag)
            size--;
        else
            size++;
    }
    void enqueue(Player *player)
    {
        Node *newNode = new Node(player);
        if (rear == nullptr)
        {
            front = newNode;
            rear = front;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }
    Player *dequeue()
    {
        if (size == 0)
        {
            throw underflow_error("Queue is empty");
        }
        Node *curr = front;
        Node *prev = nullptr;
        Player *player = curr->player;
        while (curr && player->isWithdrawn())
        {
            prev = curr;
            curr = curr->next;
            if (curr != nullptr)
                player = curr->player;
        }
        if (!curr)
            return nullptr;
        if (curr == rear)
        {
            rear = prev;
        }
        if (curr == front)
        {
            front = curr->next;
        }
        else
        {
            prev->next = curr->next;
        }
        delete curr;
        size--;
        return player;
    }
    bool isEmpty()
    {
        return size == 0;
    }
    int getSize()
    {
        return size;
    }
    ~NormalQueue()
    {
        while (front != nullptr)
        {
            Node *temp = front;
            front = front->next;
            delete temp;
        }
    }
};

class VIPQueue
{
private:
    Node *front;
    int size;
    int totalSize;

public:
    VIPQueue()
    {
        size = 0;
        totalSize = 0;
        front = nullptr;
    }
    void withdraw(bool flag)
    {
        if (flag && size > 0)
            size--;
        else if (!flag)
            size++;
    }
    void enqueue(Player *player)
    {
        Node *temp = new Node(player);
        if (totalSize == 0)
        {
            front = temp;
            size++;
            totalSize++;
            return;
        }
        Node *curr = front;
        Node *prev = nullptr;
        while (curr != nullptr && ((curr->player->getLevel() > temp->player->getLevel()) || ((curr->player->getLevel() == temp->player->getLevel()) && curr->player->getArrivalOrder() < temp->player->getArrivalOrder())))
        {
            prev = curr;
            curr = curr->next;
        }
        if (prev == nullptr)
        {
            temp->next = front;
            front = temp;
        }
        else if (curr == nullptr)
        {
            prev->next = temp;
        }
        else
        {
            temp->next = curr;
            prev->next = temp;
        }
        size++;
        totalSize++;
        return;
    }
    Player *dequeue()
    {
        if (size == 0)
        {
            throw underflow_error("Queue is empty");
        }
        Player *temp = front->player;
        Node *curr = front;
        Node *prev = nullptr;
        while (curr && temp->isWithdrawn())
        {
            prev = curr;
            curr = curr->next;
            if (curr != nullptr)
                temp = curr->player;
        }
        if (!curr)
            return nullptr;
        if (curr == front)
            front = front->next;
        else
            prev->next = curr->next;
        size--;
        totalSize--;
        delete curr;
        return temp;
    }

    void remove(int id)
    {
        Node *curr = front;
        Node *prev = nullptr;

        while (curr != nullptr)
        {
            if (curr->player->getId() == id)
            {
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr)
            return;
        if (prev == nullptr)
        {
            front = curr->next;
            delete curr;
            size--;
            totalSize--;
            return;
        }
        prev->next = curr->next;
        delete curr;
        size--;
        totalSize--;
        return;
    }

    bool isEmpty()
    {
        return size == 0;
    }
    int getSize()
    {
        return size;
    }
    ~VIPQueue()
    {
        Node *curr = front;
        while (curr != nullptr)
        {
            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
};
// Node for stack------------------------------------
class StackNode
{
public:
    Player *player;
    Player *prevPlayer;
    StackNode *next;
    string operation;
    StackNode(Player *p, string o)
    {
        player = p;
        operation = o;
        prevPlayer = nullptr;
        next = nullptr;
    }
    StackNode(Player *p, Player *prevP, string o)
    {
        player = p;
        prevPlayer = prevP;
        operation = o;
        next = nullptr;
    }
};

class UNDOStack
{
private:
    StackNode *top;
    int size;

public:
    UNDOStack()
    {
        top = nullptr;
        size = 0;
    }
    void push(StackNode *s)
    {
        if (size == 0)
        {
            top = s;
        }
        else
        {
            s->next = top;
            top = s;
        }
        size++;
        return;
    }
    StackNode *pop()
    {
        if (size == 0 || top == nullptr)
            throw underflow_error("Empty stack");
        StackNode *node = top;
        top = top->next;
        size--;
        return node;
    }
    int getSize()
    {
        return size;
    }
    ~UNDOStack()
    {
        while (top != nullptr)
        {
            StackNode *temp = top;
            top = top->next;
            if (temp->operation == "PLAY")
                delete temp->player;
            delete temp;
        }
    }
};

class hashTable
{
private:
    static const int size = 100;
    vector<vector<Player *>> table;
    int hashFunction(int id)
    {
        int temp = id % size;
        if (temp < 0)
            return -1 * temp;
        return temp;
    }

public:
    hashTable() : table(size)
    {
    }
    bool insert(Player *node)
    {
        int key = hashFunction(node->getId());
        for (int i = 0; i < table[key].size(); i++)
        {
            if (table[key][i]->getId() == node->getId())
            {
                return false;
            }
        }
        table[key].push_back(node);
        return true;
    }
    Player *search(int id)
    {
        int key = hashFunction(id);
        for (int i = 0; i < table[key].size(); i++)
        {
            if (table[key][i]->getId() == id)
            {
                return table[key][i];
            }
        }
        return nullptr;
    }
    Player *remove(int id)
    {
        int key = hashFunction(id);
        for (int i = 0; i < table[key].size(); i++)
        {
            if (table[key][i]->getId() == id)
            {
                Player *temp = table[key][i];
                table[key].erase(table[key].begin() + i);
                return temp;
            }
        }

        return nullptr;
    }

    ~hashTable()
    {
        for (int i = 0; i < table.size(); i++)
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                delete table[i][j];
            }
        }
    }
};

class PingPongManager
{
private:
    hashTable table;
    NormalQueue normalQueue;
    VIPQueue vipQueue;
    UNDOStack undoStack;
    int arrivalOrder;

    void Withdraw(Player *player)
    {
        player->setWithdraw(true);
        if (player->getType() == "VIP")
        {
            vipQueue.withdraw(true);
        }
        else
        {
            normalQueue.withdraw(true);
        }
    }
    void UndoWithdraw(Player *player)
    {
        player->setWithdraw(false);
        if (player->getType() == "VIP")
        {
            vipQueue.withdraw(false);
        }
        else
        {
            normalQueue.withdraw(false);
        }
    }

public:
    PingPongManager()
    {
        arrivalOrder = 0;
    }

    void REGISTER(int id, string name, int level, string type)
    {
        Player *player = new Player(id, name, level, type, arrivalOrder); // new player
        if (table.search(id) != nullptr)
        {
            player->setWithdraw(false);
            delete player;
            return;
        }
        if (type == "NORMAL")
        {
            normalQueue.enqueue(player);
        }
        else if (type == "VIP")
        {
            vipQueue.enqueue(player);
        }
        table.insert(player);
        StackNode *stackItem = new StackNode(player, "REGISTER");
        undoStack.push(stackItem);
        arrivalOrder++;
    }
    void PLAY()
    {
        if (normalQueue.getSize() == 0 && vipQueue.getSize() == 0)
        {
            cout << "NO PLAYERS" << endl;
            return;
        }
        Player *temp = nullptr;
        if (vipQueue.getSize() != 0)
        {
            temp = vipQueue.dequeue();
        }
        if (!temp && normalQueue.getSize() != 0)
        {
            temp = normalQueue.dequeue();
        }
        if (!temp)
        {
            cout << "NO PLAYERS" << endl;
            return;
        }
        StackNode *stackItem = new StackNode(temp, "PLAY");
        undoStack.push(stackItem);
        table.remove(temp->getId());
        cout << temp->getId() << " " << temp->getName() << endl;
    }

    void BOOST(int id, int x)
    {
        Player *temp = table.search(id);
        if (temp == nullptr || temp->getType() == "NORMAL" || temp->isWithdrawn())
            return;
        Player *old = new Player(*temp); // new player copy
        temp->setLevel(temp->getLevel() + x);
        StackNode *stackItem = new StackNode(temp, old, "BOOST");
        undoStack.push(stackItem);
        if (temp->getType() == "VIP")
        {
            vipQueue.remove(id);
            vipQueue.enqueue(temp);
        }
    }
    void WITHDRAW(int id)
    {
        Player *temp = table.search(id);
        if (temp == nullptr || temp->isWithdrawn())
            return;
        Withdraw(temp);
        StackNode *stackItem = new StackNode(temp, "WITHDRAW");
        undoStack.push(stackItem);
    }
    void UNDO()
    {
        if (undoStack.getSize() == 0)
            return;
        StackNode *temp = undoStack.pop();

        if (temp->operation == "REGISTER")
        {

            Player *playerPtr = table.search(temp->player->getId());

            if (playerPtr != nullptr)
            {
                Withdraw(playerPtr);
                table.remove(playerPtr->getId());
            }
        }
        else if (temp->operation == "PLAY")
        {
            Player *player = temp->player;

            if (player->getType() == "VIP")
                vipQueue.enqueue(player);
            else
                normalQueue.enqueue(player);
            table.insert(player);
        }
        else if (temp->operation == "BOOST")
        {
            Player *player = table.search(temp->player->getId());
            player->setLevel(temp->prevPlayer->getLevel());
            if (player->getType() == "VIP")
            {
                vipQueue.remove(player->getId());
                vipQueue.enqueue(player);
            }
            if (temp->prevPlayer != nullptr)
                delete temp->prevPlayer;
        }
        else if (temp->operation == "WITHDRAW")
        {
            Player *player = table.search(temp->player->getId());
            UndoWithdraw(player);
        }
        temp->next = nullptr;
        delete temp;
        return;
    }
    void input()
    {
        string input;
        cin >> input;
        string temp;
        for (char c : input)
        {
            temp += toupper(c);
        }
        if (temp == "REGISTER")
        {
            int id, level;
            string name, type;
            cin >> id >> name >> level >> type;
            string tempType;
            for (char c : type)
            {
                tempType += toupper(c);
            }
            this->REGISTER(id, name, level, tempType);
        }
        else if (temp == "PLAY")
        {
            PLAY();
        }
        else if (temp == "BOOST")
        {
            int id, x;
            cin >> id >> x;
            this->BOOST(id, x);
        }
        else if (temp == "WITHDRAW")
        {
            int id;
            cin >> id;
            this->WITHDRAW(id);
        }
        else if (temp == "UNDO")
        {
            this->UNDO();
        }
        else if (temp == "STATUS")
        {
            this->STATUS();
        }
    }
    void STATUS()
    {
        cout << "VIP Count: " << vipQueue.getSize() << " Normal Count: " << normalQueue.getSize() << endl;
    }
};

int main()
{
    long long input;
    cin >> input;
    PingPongManager manager;
    while (input--)
        manager.input();

    return 0;
}