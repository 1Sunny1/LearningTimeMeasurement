#include "TimeMeasurement.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>

TimeMeasurement::TimeMeasurement() noexcept : timer{ time(nullptr) }, tpStart{ clock::now() } {
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

TimeMeasurement::Commands TimeMeasurement::manageUserInput() {
	std::string userInput;
	while(true) {
		std::cout << "\n>> ";
		std::getline(std::cin, userInput);
		std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
		if (auto found = std::find_if(commands.begin(), commands.end(), [&userInput](const auto &value) { return userInput == value.second; }); found == commands.end()) //if NOT found! pay attention!
			std::cout << UNRECOGNISED_COMMAND;
		else
			return found->first;
	}
}

void TimeMeasurement::run() {
	TimeMeasurement::Commands managed;
	while (true) {
		managed = manageUserInput();
		switch (managed) {
		case Commands::START:    countTime();		     break;
		case Commands::ACTUAL:   showPassedTime();       break;
		case Commands::BREAK:    stopCountingTime();     break;
		case Commands::CONTINUE: continueCountingTime(); break;
		case Commands::END:      terminateApplication(); break;
		case Commands::HELP:     showHelpDescription();  break;
		}
	}
}

void TimeMeasurement::countTime() {
	std::cout << "countTime() under development!\n";
}

void TimeMeasurement::showPassedTime() const {
	std::cout << "Elapsed time: " << elapsed();
}

void TimeMeasurement::insertCommand(Commands command, const std::string &strCommand) {
	commands.insert(std::make_pair(command, strCommand));
}

void TimeMeasurement::showHelpDescription() const {
	std::cout << "TimeMeasurement::showHelpDescription() under development!\n";
}

void TimeMeasurement::insertAllCommands() {
	insertCommand(Commands::ACTUAL,   "ACTUAL");
	insertCommand(Commands::BREAK,	  "BREAK");
	insertCommand(Commands::START,	  "START");
	insertCommand(Commands::END,	  "END");
	insertCommand(Commands::HELP,	  "HELP");
	insertCommand(Commands::CONTINUE, "CONTINUE");
}

void TimeMeasurement::stopCountingTime() {
	std::cout << "TimeMeasurement::stopCountingTime() under development!\n";
}

void TimeMeasurement::continueCountingTime() {
	std::cout << "TimeMeasurement::continueCountingTime() under development!\n";
}

void TimeMeasurement::terminateApplication() {
	std::cout << "TimeMeasurement::terminateApplication() under development!\n";
	saveActualData();
	exit(0);
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