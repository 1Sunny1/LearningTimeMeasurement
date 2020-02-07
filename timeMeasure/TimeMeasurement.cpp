#include "TimeMeasurement.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>

TimeMeasurement::TimeMeasurement() noexcept : timer{ time(nullptr) }, tpStart(clock::now()) {
	timeOfStart = std::make_unique<tm>(*gmtime(&timer));
	date = makeDate();
	strTime = makeStartTime();
	printTimeOfStart();
	insertAllCommands();
}

void TimeMeasurement::saveActualData() {
	std::fstream file("data.txt");
	if (!file.good())
		std::cout << COULD_NOT_LOAD_FILE;	
	else 
		saveToFile(file);
}

std::string TimeMeasurement::manageUserInput() {
	std::string userInput;
	while(true) {
		std::cout << "\n>> ";
		std::getline(std::cin, userInput);
		std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
		if (auto found = std::find_if(commands.begin(), commands.end(), [&userInput](const auto &value) { return userInput == value.second; }); found == commands.end()) //if NOT found! pay attention!
			std::cout << UNRECOGNISED_COMMAND;
		else
			break;
	}
	return userInput;
}

void TimeMeasurement::run() {
	auto manager = manageUserInput();
	while (manager != "END") {
		countTime();
		manager = manageUserInput();
	
	}
	saveActualData(); //if user types 'end' - not implemented yet;
}

void TimeMeasurement::countTime() {
	std::cout << "Elapsed time: " << elapsed();
}

void TimeMeasurement::insertCommand(Commands command, const std::string &strCommand) {
	commands.insert(std::make_pair(command, strCommand));
}

void TimeMeasurement::insertAllCommands() {
	insertCommand(Commands::ACTUAL,   "ACTUAL");
	insertCommand(Commands::BREAK,	  "BREAK");
	insertCommand(Commands::START,	  "START");
	insertCommand(Commands::END,	  "END");
	insertCommand(Commands::HELP,	  "HELP");
	insertCommand(Commands::CONTINUE, "CONTINUE");
}

std::string TimeMeasurement::makeDate() {
	std::ostringstream oss;
	oss << (timeOfStart->tm_year + 1900) << "-" << std::setw(2) << std::setfill('0') << (timeOfStart->tm_mon + 1) << "-" << std::setw(2) << std::setfill('0') << timeOfStart->tm_mday;
	return oss.str();
}

std::string TimeMeasurement::makeStartTime() {
	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << (timeOfStart->tm_hour + 1) << ":" << std::setw(2) << std::setfill('0') << (timeOfStart->tm_min) << ":" << std::setw(2) << std::setfill('0') << timeOfStart->tm_sec;
	return oss.str();
}

void TimeMeasurement::printTimeOfStart() const {
	std::cout << "Time of start: " << strTime;
}

double TimeMeasurement::elapsed() const {
	return std::chrono::duration_cast<second>(clock::now() - tpStart).count();
}

void TimeMeasurement::reset() {
	tpStart = clock::now();
}

void TimeMeasurement::saveToFile(std::fstream &file) {
	file << "Date: " + date << '\n';
	file << "Time of start: " + strTime << '\n';
	file << "Passed time: " << elapsed() << '\n';
}