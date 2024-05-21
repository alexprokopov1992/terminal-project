#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
using namespace std::filesystem;

void create_file_in_folder(std::string file_name, std::string folder_name, std::string text)
{
    path directorypath = folder_name;
    if (!exists(directorypath)) {
        create_directory(directorypath);
        cout << "Directory created: " << directorypath << endl;
    }

    path filepath = directorypath / file_name;
    ofstream file(filepath);
    if (file.is_open()) {
        file << text;
        file.close();
        cout << "File created: " << filepath << endl;
    }
    else {
        cerr << "Failed to create file: " << filepath << endl;
    }
}

int main() {
    create_file_in_folder("1.txt", "test", "Good evening");
    return 0;
}