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
	return current_location + " ";
}

void explorer::printCurrentLocation() {
	cout << this->getCurrentLocation();
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
		Working = false;
		return true;
	}

	if (lastCommand[0] == UPPER_DIRECTORY_COMMAND) {
		this->goUpDirectory();
		return true;
	}


	if (lastCommand[0] == HELP_COMMAND) {
		this->printHelp();
		return true;
	}

	if (lastCommand[0] == OPEN_NEW_FILE_COMMAND) {
		this->doFile();
		return true;
	}

	else {
		cout << " got unsupported command!\n";
		return false;
	}
}

void explorer::exit()
{
	if (lastCommand[0] == TERMINATE_COMMAND) 
	{
		
		Working = false;

	}
}
void explorer::doDir()
{
	while (true)
	{
		
	}

}

void explorer::doFile()
{
	if (lastCommand[0] == OPEN_NEW_FILE_COMMAND)
	{
		string a;
		cin >> a;
		ifstream fin(a);
		if (fin.is_open()) cout << "file created";
		else cout << "file have not created , try again";	
	}
}
