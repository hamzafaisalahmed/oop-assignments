#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

class OpenFileError : public runtime_error
{
public:
    OpenFileError() : runtime_error("Error opening file: restricted access or not found") {}
};

class FileHandler
{
    fstream file;
    string filename;
    string mode;

public:
    FileHandler(string name) : filename(name) {}
    void open(string m)
    {
        mode = m;
        if (mode == "read")
            file.open(filename, ios::in);
        else if (mode == "write")
            file.open(filename, ios::out | ios::app);
        if (!file.is_open())
            throw OpenFileError();
        else
            cout << "Sucess!" << endl;
    }
    void read()
    {
        if (!file.is_open())
            throw OpenFileError();
        if (mode == "write")
            throw runtime_error("Attemped to read from file opened in write mode");
        string content;
        while (getline(file, content))
        {
            cout << content << endl;
        }
    }
    void write(string data)
    {
        if (!file.is_open())
            throw OpenFileError();
        if (mode == "read")
            throw runtime_error("Attemped to write to file opened in read mode");
        file << data << endl;
    }
    void close()
    {
        if (file.is_open())
        {
            file.close();
            cout << "Closed file" << endl;
        }
    }

    ~FileHandler()
    {
        close();
    }
};
int main()
{
    string mode[2] = {"read", "write"};
    try
    {

        FileHandler fh("test.txt");
        fh.open(mode[1]);
        fh.write("test o_o");
        fh.close();

        fh.open(mode[0]);
        fh.read();
        fh.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }

    std::cout << "\nTesting Error Case" << endl;

    // 2. Testing a Failure (File that doesn't exist/No permission)
    try
    {
        FileHandler bad("/root/secret.txt");
        bad.open(mode[0]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "CAUGHT EXPECTED ERROR: " << e.what() << std::endl;
    }

    return 0;
}