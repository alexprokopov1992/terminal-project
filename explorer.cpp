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

	if (lastCommand[0] == OPEN_FILE_COMMAND) {
		this->openFile();
		return true;
	}

	if (lastCommand[0] == DELETE_FOLDER_COMMAND) {
		this->deleteFolder();
		return true;
	}

	if (lastCommand[0] == OPEN_FOLDER_COMMAND) {
		this->openFolder();
		return true;
	}

	if (lastCommand[0] == CREATE_NEW_FILE_COMMAND) {
		this->createFile();
		return true;
	}

	if (lastCommand[0] == CREATE_FOLDER_COMMAND) {
		this->createFolder();
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
	for (const auto& entry : directory_iterator(path))
	{
		std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ")
			<< entry.path().filename().string() << std::endl;
	}

}

void explorer::createFile()
{
	cout << "creating file\n";

	string file_path = this->getCurrentLocation() + lastCommand[1];

	std::filesystem::path path{ file_path };

	if (std::filesystem::exists(path)) {
		cout << "Error: File " << lastCommand[1] << " already exists\n";
		return;
	}

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
	cout << "File " << lastCommand[1] << " created\n";

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
	string oldFilename = lastCommand[1];
	string fileLocation = this->getCurrentLocation() + oldFilename;
	string newFilename = lastCommand[2];

	try
	{
		// Rename the file
		filesystem::rename(fileLocation, newFilename);
		std::cout << "File renamed successfully!" << std::endl;
	}
	catch (const filesystem::filesystem_error& e)
	{
		std::cerr << "Error renaming file: " << e.what() << std::endl;
	}
}

void explorer::openFolder()
{
	string folder_path = this->getCurrentLocation() + lastCommand[1];

	if (!exists(folder_path) || !is_directory(folder_path))
	{
		std::cout << "Folder doe not exist or it is not a directory /n" << folder_path << std::endl;
		return;
	}

	std::cout << "folder contains: " << folder_path << ":" << std::endl;
	for (const auto& entry : directory_iterator(folder_path))
	{
		std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ")
			<< entry.path().filename().string() << std::endl;
	}

	location.push_back(lastCommand[1]);
}


void explorer::createFolder()
{
	string folder_path = this->getCurrentLocation() + lastCommand[1];

	try {
		if (create_directory(folder_path)) {
			std::cout << "Folder created: " << folder_path << std::endl;
		}
		else {
			std::cout << "Folder already exists or failed to create: " << folder_path << std::endl;
		}
	}
	catch (const filesystem_error& e) {
		std::cerr << "Error creating folder: " << e.what() << std::endl;
	}
}

void explorer::deleteFolder()
{

	string folder_path = this->getCurrentLocation() + lastCommand[1];

	try {


		std::uintmax_t numDeleted = remove_all(folder_path);

		if (numDeleted > 0) {
			std::cout << "Folder and contents deleted: " << folder_path << "\n";
			std::cout << "Total items deleted: " << numDeleted << "\n";
		}
		else {
			std::cout << "Folder not found or already empty: " << folder_path << "\n";
		}
	}
	catch (const filesystem_error& e)
	{
		std::cerr << "Error deleting folder: " << e.what() << "\n";
	}
}

void explorer::openFile()
{
	std::string filename = lastCommand[1];

	// Check if the file exists using std::filesystem
	if (!exists(filename))
	{
		std::cerr << "Error: File '" << filename << "' does not exist.\n";
	}

	// Open the file for reading
	std::ifstream inputFile(filename);

	if (!inputFile)
	{
		std::cerr << "Error: Could not open the file '" << filename << "'.\n";
	}

	// Read the file content
	std::string line;
	while (std::getline(inputFile, line))
	{
		std::cout << line << "\n";
	}
}
