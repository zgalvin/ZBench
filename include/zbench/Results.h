#pragma once

#include "PlatformDefinitions.h"
#include "Timer.h"
WALL_WRN_PUSH
#include <vector>
#include <string>
WALL_WRN_POP

namespace zbench
{

struct ExperimentInfo
{
	std::string test_name;
	std::string arg;
	constexpr static int NAME_LENGTH = 20;

	ExperimentInfo(const std::string & name, const std::string & arg):
		test_name(name),
		arg(arg)
	{}

	ExperimentInfo(const std::string & name) :
		ExperimentInfo(name, "n/a")
	{	}

	ExperimentInfo() = default;
	ExperimentInfo(ExperimentInfo const&) noexcept = default;
	ExperimentInfo& operator=(ExperimentInfo const&) noexcept = default;
	ExperimentInfo(ExperimentInfo&& r) noexcept = default;
	ExperimentInfo& operator=(ExperimentInfo&& r) noexcept = default;
};

struct Result
{
	std::vector<Timer::Duration> sample_times;

	Result() = default;
	Result(Result const&) noexcept = default;
	Result& operator=(Result const&) noexcept = default;
	Result(Result&& r) noexcept = default;
	Result& operator=(Result&& r) noexcept = default;

	void PrepareForTests(const int num_tests)
	{
		sample_times.reserve((size_t)num_tests);
	}
};

} // namespace zbench