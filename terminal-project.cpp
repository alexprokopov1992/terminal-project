#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
using namespace std::filesystem;

int main() {
    path directorypath = "mydirectory";
    if (!exists(directorypath)) {
        create_directory(directorypath);
        cout << "Directory created: " << directorypath << endl;
    }

    path filepath = directorypath / "my_file.txt";
    ofstream file(filepath);
    if (file.is_open()) {
        file << "Hello, FileSystem!";
        file.close();
        cout << "File created: " << filepath << endl;
    }
    else {
        cerr << "Failed to create file: " << filepath << endl;
    }

    return 0;
}