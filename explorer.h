#pragma once
#include <string.h>
#include <vector>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>
#include "resource.h"


using namespace std;
using namespace std::filesystem;

class explorer
{
private:
	std::vector <std::string> location;
	std::vector <std::string> lastCommand = {};
	bool Working = true;
public:
	explorer();
	std::string getCurrentLocation();
	void printCurrentLocation();
	void getCommand();
	bool executeLastCommand();
	bool isWorking() { return Working; }
private:
	bool get_commands_vector(std::string line);
	void printHelp();
	void goUpDirectory();
	void exit();
	void doFile();
	void doDir();
};

