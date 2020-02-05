#include "TimeMeasurement.h"
#include <iostream>
#include <algorithm>

TimeMeasurement::TimeMeasurement() noexcept : actualTime{ time(nullptr) } {
	std::cout << "Starting counting...\nTime of start: ";
	showActualTime();
	insertAllCommands();
}

void TimeMeasurement::saveActualData() {
	std::cout << "\nvoid TimeMeasurement::saveActualData under development.\n";
}

std::string TimeMeasurement::manageUserInput() {
	std::string userInput;
	while(true) {
		std::cout << "\n>> ";
		std::getline(std::cin, userInput);
		std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
		if (auto found = std::find_if(commands.begin(), commands.end(), [&userInput](const auto &value) { return userInput == value.second; }); found == commands.end())
			std::cout << UNRECOGNISED_COMMAND;
		else
			break;
	}
	return userInput;
}

void TimeMeasurement::run() {
	auto manager = manageUserInput();
	while (manager != "END" &&  manager != "BREAK") {
		countTime();
		manager = manageUserInput();
	}
}

void TimeMeasurement::countTime() {
	std::cout << "\nvoid TimeMeasurement::countTime under development.\n";
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

void TimeMeasurement::showActualTime() {
	auto time = gmtime(&actualTime);
	std::cout << 1 + time->tm_hour << ':' << time->tm_min << ':' << time->tm_sec;
}
