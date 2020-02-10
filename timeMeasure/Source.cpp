#include "TimeMeasurement.h"
#include <memory>

int main() {
	auto instance = std::make_unique<TimeMeasurement>();
	instance->run();
}