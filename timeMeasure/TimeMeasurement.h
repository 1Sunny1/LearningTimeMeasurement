#ifndef TIMEMEASUREMENT_H_
#define TIMEMEASUREMENT_H_

#include <string>
#include <ctime>
#include <unordered_map>
#include <memory>
#include <chrono>

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
	using clock = std::chrono::high_resolution_clock;
	using second = std::chrono::duration<double, std::ratio<1> >;

public:
	explicit	TimeMeasurement() noexcept;
	void		run();
	void		printTimeOfStart() const;
	double		elapsed() const;
	void		reset();

private:
	void			saveActualData();
	void			saveToFile(std::fstream &);
	Commands		manageUserInput();
	void			countTime();
	void			insertCommand(Commands, const std::string &);
	void			insertAllCommands();
	std::string		makeDate();
	std::string		makeStartTime();
	

private:
	time_t												timer;
	std::unique_ptr<tm>									timeOfStart;
	std::unordered_map<Commands, std::string>			commands;
	std::string											date;
	std::string											strTime;
	std::chrono::time_point<clock>						tpStart;

private:
	const std::string									UNRECOGNISED_COMMAND{ "Unrecognized command. Please try again: " };
	const std::string									COULD_NOT_LOAD_FILE{ "Couldn't load file!" };
	
};
#endif // !TIMEMEASUREMENT_H_