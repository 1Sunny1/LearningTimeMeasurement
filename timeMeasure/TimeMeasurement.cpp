#include "TimeMeasurement.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <numeric>

TimeMeasurement::TimeMeasurement() noexcept : timer{ time(nullptr) } {
	timeOfStart = std::make_unique<tm>(*gmtime(&timer));
	date = makeDate();
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
	std::cout << "To begin, type \"start\" or \"help\"\n";
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
	std::cout << "Counting started.\n";
	IS_STARTED = true;
	strTime = makeStartTime();
	printTimeOfStart();
	reset();
}

void TimeMeasurement::showPassedTime() const {
	if (IS_STARTED) {
		const auto temporary = elapsed();
		const auto total = std::accumulate(vElapsedTimes.begin(), vElapsedTimes.end(), 0.0) + elapsed();
		std::cout << "actually elapsed time: " << temporary;
		std::cout << "\ntotal elapsed time during program execute: " << total << '\n';
	}
	else
		std::cout << "Counting is not even started, you cannot show actual results.\n";
}

void TimeMeasurement::insertCommand(Commands command, const std::string &strCommand) {
	commands.insert(std::make_pair(command, strCommand));
}

void TimeMeasurement::showHelpDescription() const {
	std::cout << "\nThese are commands used in this program:\n\nstart - start counting time until stopped\n\n"
		<< "actual - show actual statistics about time passed and time of start\n\nbreak - temporarily stops counting time"
		<< " until continued\n\ncontinue - program continues counting time after a break\n\nend - stops counting, saves"
		<< " results to file and terminates program\n\nhelp - shows all commands available (you are here)\n";
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
	if (IS_STARTED) {
		std::cout << "Stopped counting time.\n";
		vElapsedTimes.push_back(elapsed());
		IS_BREAK = true;
	}
	else
		std::cout << "You can't stop counting if it is not counting :D\n";
}

void TimeMeasurement::continueCountingTime() {
	if (IS_BREAK) {
		std::cout << "Counting time again after a break.\n";
		reset();
		IS_BREAK = false;
	}
	else
		std::cout << "You can't continue if there was no break!\n";
}

void TimeMeasurement::terminateApplication() {
	if (!IS_BREAK)
		vElapsedTimes.push_back(elapsed());

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
	std::cout << "\nTime of start: " << strTime;
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
	file << "Passed time: " << std::accumulate(vElapsedTimes.begin(), vElapsedTimes.end(), 0.0) << '\n';
}