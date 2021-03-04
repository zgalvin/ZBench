#ifndef RESULT_H
#define RESULT_H

#include "PlatformDefinitions.h"
WALL_WRN_PUSH
#include <vector>
#include <string>
WALL_WRN_POP

struct Result
{
	Result(const char * const test_name_):
		Result(test_name_, "n/a")
	{

	}

	Result(const char* const test_name_, const char * const arg_) :
		test_name(test_name_),
		arg(arg_),
		sample_times()
	{
	}

	void PrepareForTests(const int numTests)
	{
		sample_times.reserve((size_t)numTests);
	}

	std::string test_name;
	std::string arg;
	std::vector<long long> sample_times;

	Result(Result const&)noexcept= delete;
	Result& operator=(Result const&) = delete;

	Result(Result&& r)noexcept:
		test_name(std::move(r.test_name)),
		arg(std::move(arg)),
		sample_times(std::move(sample_times))
	{	}

	Result& operator=(Result&& r) noexcept
	{
		test_name = std::move(r.test_name);
		arg = std::move(r.arg);
		sample_times = std::move(sample_times);
	}

	const static int NAME_LENGTH = 20;
};

#endif // !RESULTS_H