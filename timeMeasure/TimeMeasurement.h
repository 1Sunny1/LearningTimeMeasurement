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
	void		printTimeOfStart() const;
	void		showPassedTime();
	void		run();

private:
	double					elapsed() const;
	std::string				timeInHMS(const double);
	std::string				makeDate();
	std::string				makeStartTime();
	Commands				manageUserInput();
	void					saveToFile(std::ofstream &);
	void					insertCommand(Commands, const std::string &);
	void					showHelpDescription() const;
	void					saveActualData();
	void					countTime();
	void					insertAllCommands();
	void					stopCountingTime();
	void					continueCountingTime();
	void					terminateApplication();
	void					reset();

private:
	time_t												timer;
	std::unique_ptr<tm>									timeOfStart;
	std::unordered_map<Commands, std::string>			commands;
	std::string											date;
	std::string											strStartTime;
	std::chrono::time_point<clock>						tpStart;
	std::vector<double>									vElapsedTimes;
	int													elapsed_val;

private:
	const std::string									UNRECOGNISED_COMMAND{ "Unrecognized command. Please try again:\n" };
	const std::string									COULD_NOT_LOAD_FILE{ "Couldn't load file!\n" };
	bool												IS_STARTED = false;
	bool												IS_BREAK = false;
};
#endif // !TIMEMEASUREMENT_H_