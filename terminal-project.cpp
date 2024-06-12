#include <filesystem>
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
#include "resource.h"

using namespace std;
using namespace std::filesystem;


vector <string> get_commands_vector(string &input);
void execute_command(vector <string>&);

int main() {
    
    string filepath = __FILE__;
    int pos = filepath.length();
    for (pos; pos >= 0; pos--)
    {
        if (filepath[pos] == '\\') break;
    }
    string location = "";
    for (int i = 0; i < pos + 1; i++) location += filepath[i];
    while (true)
    {
        string line;
        cout << location;
        getline(cin, line);
        vector <string> commands = get_commands_vector(line);
        execute_command(commands);
        if (line == "exit") break;
    }
    return 0;
}

vector <string> get_commands_vector(string& input)
{
    istringstream iss(input);
    vector<string> words;
    string word;
    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}

void execute_command(vector <string>& commands_vector)
{
    if (commands_vector[0] == HELP_COMMAND) {
        cout << "print help\n";
        return;
    }
    else {
        cout << "got unsupported command!\n";
    }
}