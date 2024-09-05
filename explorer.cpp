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

	if (lastCommand[0] == UPPER_DIRECTORY_COMMAND) {
		this->goUpDirectory();
		return true;
	}

	if (lastCommand[0] == CREATE_NEW_FILE_COMMAND)
	{
		
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


}

void explorer::createFile()
{
	cout << "creating file\n";
	
	string file_path = getCurrentLocation() + lastCommand[1];

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
	

}
