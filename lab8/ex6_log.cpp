#include <iostream>
#include <string>

using namespace std;

class log
{
public:
    virtual void logMessage(const string &msg) = 0;
    virtual ~log() {}
};

class ConsoleLogger : public log
{
public:
    void logMessage(const string &msg) override
    {
        cout << "[CONSOLE] " << msg << endl;
    }
};

class FileLogger : public log
{
public:
    void logMessage(const string &msg) override
    {
        cout << "[FILE] " << msg << endl;
    }
};

class DatabaseLogger : public log
{
public:
    void logMessage(const string &msg) override
    {
        cout << "[DATABASE] " << msg << endl;
    }
};

int main()
{
    string msg = "Log message";
    log *logger = new ConsoleLogger();
    logger->logMessage(msg);
    delete logger;
    logger = new FileLogger();
    logger->logMessage(msg);
    delete logger;
    logger = new DatabaseLogger();
    logger->logMessage(msg);
    delete logger;
}