#ifndef TIMEMEASUREMENT_H_
#define TIMEMEASUREMENT_H_

#include <string>
#include <ctime>
#include <unordered_map>

class TimeMeasurement final {
public:
	enum class Commands : int {
		START,
		BREAK,
		CONTINUE,
		ACTUAL,
		END,
		HELP
	};

public:
	explicit	TimeMeasurement() noexcept;
	void		run();
	void		showActualTime();

private:
	void			saveActualData();
	std::string		manageUserInput();
	void			countTime();
	void			insertCommand(Commands, const std::string &);
	void			insertAllCommands();

private:
	time_t												actualTime;
	std::unordered_map<Commands, std::string>			commands;
	const std::string									UNRECOGNISED_COMMAND{ "Unrecognized command. Please try again: " };
};

#endif // !TIMEMEASUREMENT_H_

