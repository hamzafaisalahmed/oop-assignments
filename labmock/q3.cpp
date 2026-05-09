#include <iostream>
#include <vector>
#include <stdexcept>
#include <functional>
using namespace std;

class StackUnderflow : public exception
{
public:
    const char *what() const noexcept override
    {
        return "Stack underflow: cannot pop or peek an empty stack.";
    }
};

template <typename T>
class Stack
{
    vector<T> stack;

public:
    void push(const T &value)
    {
        stack.push_back(value);
    }
    void pop()
    {
        if (stack.size() == 0)
            throw StackUnderflow();
        stack.pop_back();
    }
    T peek() const
    {
        if (stack.size() == 0)
            throw StackUnderflow();
        return stack.back();
    }
    bool isEmpty() const
    {
        return (stack.size() == 0);
    }
    T getAt(int index) const
    {
        return stack[index];
    }
    int getSize() const { return stack.size(); }
    ~Stack() = default;
};

template <typename T>
class UndoRedoManager
{
    Stack<T> undoStack;
    Stack<T> redoStack;

public:
    void performAction(const T &action)
    {
        undoStack.push(action);
        while (redoStack.getSize() != 0)
        {
            redoStack.pop();
        }
    }
    void undo()
    {
        if (undoStack.getSize() != 0)
        {
            redoStack.push(undoStack.peek());
            undoStack.pop();
            cout << "Undone: " << redoStack.peek() << endl;
            return;
        }
        cout << "Nothing to undo." << endl;
    }
    void redo()
    {
        if (redoStack.getSize() != 0)
        {
            undoStack.push(redoStack.peek());
            redoStack.pop();
        }
        else
            cout << "Nothing to redo" << endl;
    }
    void showCurrentAction() const
    {
        if (!undoStack.isEmpty())
            cout << "Current action: " << undoStack.peek() << endl;
        else
            cout << "No current action" << endl;
    }

    void showIf(std::function<bool(const T &)> condition) const
    {
        bool flag = false;
        for (int i = 0; i < undoStack.getSize(); i++)
        {
            if (condition(undoStack.getAt(i)))
            {
                cout << undoStack.getAt(i) << "  ";
                flag = true;
            }
        }
        if (!flag)
            cout << " (none match)";
    }
};

int main()
{
    // ---- Part A: string actions ----
    std::cout << "=== String UndoRedoManager ===" << std::endl;
    UndoRedoManager<std::string> strManager;
    strManager.performAction("type A");
    strManager.performAction("delete word");
    strManager.performAction("paste text");
    strManager.performAction("type B");
    strManager.performAction("format bold");
    strManager.showCurrentAction();           // format bold
    strManager.undo();                        // undo format bold
    strManager.undo();                        // undo type B
    strManager.showCurrentAction();           // paste text
    strManager.redo();                        // redo type B
    strManager.showCurrentAction();           // type B
    strManager.performAction("insert image"); // new action clears redo stack
    strManager.redo();                        // Nothing to redo.
    std::cout << "\n-- Actions containing ’type’ --" << std::endl;
    strManager.showIf([](const std::string &s)
                      { return s.find("type") != std::string::npos; });
    // ---- Part B: integer actions ----
    std::cout << "\n=== Integer UndoRedoManager ===" << std::endl;
    UndoRedoManager<int> intManager;
    intManager.performAction(5);
    intManager.performAction(12);
    intManager.performAction(7);
    intManager.performAction(20);
    intManager.performAction(3);
    intManager.showCurrentAction(); // 3
    intManager.undo();              // undo 3
    intManager.undo();              // undo 20
    intManager.showCurrentAction(); // 7
    std::cout << "\n-- Integer actions greater than 10 --" << std::endl;
    intManager.showIf([](int val)
                      { return val > 10; });
    // ---- Part C: exception handling ----
    std::cout << "\n=== Exception Handling ===" << std::endl;
    Stack<std::string> emptyStack;
    try
    {
        emptyStack.pop();
    }
    catch (const StackUnderflow &e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    try
    {
        std::string top = emptyStack.peek();
    }
    catch (const StackUnderflow &e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
