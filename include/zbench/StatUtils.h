#pragma once

#include <vector>
#include <numeric>
#include "Timer.h"

namespace zbench
{

namespace StatUtils
{
	template <typename T>
	static inline T GetSampleAverage(const std::vector<T>& sample_times)
	{
		return std::accumulate(sample_times.cbegin(), sample_times.cend(), T(0)) / sample_times.size();
	}

	struct SampleStats
	{
		double average;
		double std_dev;
	};

	static inline SampleStats GetSampleStats(const std::vector<Timer::Duration>& sample_times)
	{
		SampleStats result;

		const double x = 1 / (double)(sample_times.size() - 1);
		result.average = (double)Timer::ToNanoseconds(StatUtils::GetSampleAverage(sample_times));

		double variance = 0.0;
		for (const auto & time : sample_times)
		{
			const double delta = (double)Timer::ToNanoseconds(time) - result.average;
			const double interm = delta * delta;
			variance += interm;
		}

		result.std_dev = sqrt(x * variance);

		return result;
	}
};

} // namespace zbench