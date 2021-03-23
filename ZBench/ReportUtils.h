#pragma once

#include <vector>
#include "Timer.h"

namespace zbench
{

namespace ReportUtils
{
	static long long GetSampleAverage(const std::vector<long long>& sample_times)
	{
		long long total = 0;
		for (long long const time : sample_times)
		{
			total += time;
		}

		return total / (long long)sample_times.size();
	}

	static long long GetAverageTime(const std::vector<long long>& sample_times)
	{
		Timer timer;
		const float nanos = timer.ToNanoseconds(ReportUtils::GetSampleAverage(sample_times));
		return static_cast<long long>(nanos);
	}

	struct SampleStats
	{
		double average;
		double std_dev;
	};

	static SampleStats GetSampleStats(const std::vector<long long>& sample_times)
	{
		SampleStats result;

		const double x = 1 / (double)(sample_times.size() - 1);
		result.average = static_cast<double>(ReportUtils::GetSampleAverage(sample_times));

		double variance = 0.0;
		for (const long long time : sample_times)
		{
			const double delta = time - result.average;
			const double interm = delta * delta;
			variance += interm;
		}

		result.std_dev = sqrt(x * variance);

		return result;
	}
};

} // namespace zbench