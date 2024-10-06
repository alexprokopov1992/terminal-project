#include "explorer.h"

explorer::explorer()
{
	std::string filepath = __FILE__;
	std::istringstream iss(filepath);
	std::string token;
	while (std::getline(iss, token, '\\')) {
		location.push_back(token);
	}
	location.pop_back();
}

//Function which return string of current explorer location
std::string explorer::getCurrentLocation() 
{
	std::string current_location = "";
	for (const auto element : location)
	{
		current_location += element + "\\";
	}
	return current_location;
}

void explorer::printCurrentLocation() {
	cout << this->getCurrentLocation() << " ";
}

bool explorer::get_commands_vector(std::string line)
{
	lastCommand = {};
	istringstream iss(line);
	string word;
	while (iss >> word) {
		lastCommand.push_back(word);
	}
	if (lastCommand.size() > 0) return true;
	return false;
}

void explorer::getCommand()
{
	std::string line;
	std::getline(cin, line);
	get_commands_vector(line);
}

void explorer::printHelp()
{
	cout << "Help contetnt there\n";//added \n
}

void explorer::goUpDirectory()
{
	if (location.size() > 1)
	{
		location.pop_back();
	}
	else {
		cout << "Error! You are at upper directory!\n";
	}
}


bool explorer::executeLastCommand()
{
	if (lastCommand[0] == TERMINATE_COMMAND) {
		this->exit();
		return true;
	}

	if (lastCommand[0] == SHOW_FILES_AND_DIRS_COMMAND) {
		this->showDirFiles();
		return true;
	}

	if (lastCommand[0] == UPPER_DIRECTORY_COMMAND) {
		this->goUpDirectory();
		return true;
	}

	if (lastCommand[0] == DELETE_FILE_COMMAND)
	{
		this->deleteFile();
		return true;
	}
	if (lastCommand[0] == RENAME_FILE_COMMAND)
	{
		this->renameFile();
		return true;
	}
	if (lastCommand[0] == HELP_COMMAND) {
		this->printHelp();
		return true;
	}

	if (lastCommand[0] == CREATE_NEW_FILE_COMMAND) {
		this->createFile();
		return true;
	}

	else {
		cout << " got unsupported command!\n";
		return false;
	}
}

void explorer::exit()
{		
		Working = false;
}

void explorer::showDirFiles()
{
	std::string path = this->getCurrentLocation();
	for (const auto& entry : filesystem::directory_iterator(path))
		std::cout << entry.path().filename() << std::endl;

}

void explorer::createFile()
{
	cout << "creating file\n";
	
	string file_path = this->getCurrentLocation() + lastCommand[1];

	std::filesystem::path path{ file_path };

	std::filesystem::create_directories(path.parent_path());
	
	std::ofstream ofs(path);

	if (lastCommand.size() > 2)
	{
		for (int i = 2; i <= lastCommand.size() - 1; i++)
		{
			ofs << lastCommand[i] << " ";
		}
	}
	else {
		ofs << "This is default text\n";
	}

	ofs.close();
	cout << "File" << lastCommand[1] << "created";

}

void explorer::deleteFile()
{
	string file_path = this->getCurrentLocation() + lastCommand[1];
	try {
		if (remove(file_path)) {
			std::cout << "File (" << file_path << ") deleted successfully.\n";
		}
		else {
			std::cout << "File (" << file_path << ") not exist.\n";
		}
	}
	catch (const filesystem_error& e) {
		std::cerr << "Got error deleting file: " << e.what() << '\n';
	}
}

void explorer::renameFile()
{
	namespace fs = std::filesystem;

	fs::path oldFilename = 
	fs::path newFilename = newFileName;

	try
	{
		// Rename the file
		fs::rename(oldFilename, newFilename);
		std::cout << "File renamed successfully!" << std::endl;
	}
	catch (const fs::filesystem_error& e) 
	{
		std::cerr << "Error renaming file: " << e.what() << std::endl;
	}
}