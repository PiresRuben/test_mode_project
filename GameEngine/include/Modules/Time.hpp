#pragma once

#include <unordered_map>
#include <string>

#include "Module.hpp"
#include "Utilities/PerformanceRecord.hpp"

#ifdef DEBUG
	#define StartTimedExecution(name) Time::BeginTimedExecution(name)
	#define EndTimedExecution(name) Time::TerminateTimedExecution(name)
#else
	#define StartTimedExecution(name)
	#define EndTimedExecution(name)
#endif

class Time : public Module {
public:
	Time();
	void Init() override;
	void Update() override;
	static double deltaTime;
	static double time;
#ifdef DEBUG
	static void BeginTimedExecution(const std::string& name);
	static void TerminateTimedExecution(const std::string& name);
#endif
private:
#ifdef DEBUG
	std::unordered_map<std::string, PerformanceRecord> timedExecutions;
#endif

	static Time* instance;

	unsigned int frameCount = 0;
	const double MIN_FRAMERATE_SAMPLE_DURATION = .1;
	double frameRateSampleDuration = MIN_FRAMERATE_SAMPLE_DURATION;
	double currentFrameRateSampleCounter = .0;
	double lastRecordedFps = .0;
};