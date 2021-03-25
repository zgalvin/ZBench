#pragma once

#include <vector>
#include <numeric>
#include "Timer.h"

namespace zbench
{

namespace StatUtils
{
	template <typename T>
	static long long GetSampleAverage(const std::vector<T>& sample_times)
	{
		return std::accumulate(sample_times.cbegin(), sample_times.cend(), T(0)) / sample_times.size();
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
		result.average = static_cast<double>(StatUtils::GetSampleAverage(sample_times));

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