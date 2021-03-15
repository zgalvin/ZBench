#pragma once

#include <vector>
#include "Timer.h"

namespace zbench
{

struct ReportUtils
{
public:
	static long long GetAverageTime(const std::vector<long long>& sample_times)
	{
		Timer timer;
		const float nanos = timer.ToNanoseconds(ReportUtils::GetSampleAverage(sample_times));
		return static_cast<long long>(nanos);
	}

	static long long GetSampleAverage(const std::vector<long long>& sample_times)
	{
		long long total = 0;
		for (long long const time : sample_times)
		{
			total += time;
		}

		return total / (long long)sample_times.size();
	}

	static void GetSampleStdDev(const std::vector<long long>& sample_times, double& out_stddev, double& out_average)
	{
		const double x = 1 / (double)(sample_times.size() - 1);
		out_average = static_cast<double>(ReportUtils::GetSampleAverage(sample_times));

		double variance = 0.0;
		for (const long long time : sample_times)
		{
			const double delta = time - out_average;
			const double interm = delta * delta;
			variance += interm;
		}

		out_stddev = sqrt(x * variance);
	}
};

} // namespace zbench