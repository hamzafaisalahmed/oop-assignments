#include <iostream>
#include <string>

using namespace std;

class Logger
{
public:
    void log(string message)
    {
        cout << "[LOG]: " << message << endl;
    }
};

class FileManager : private Logger
{
public:
    void saveFile(string file)
    {
        log("Saving file: " + file);
        cout << "File saved: " << file << endl;
    }
};

int main()
{
    FileManager f;
    f.saveFile("newfile.txt");
    // this works as savefile is public and log is private in main but as its only called inside filemanager it works
}