#pragma once

#include <functional>
#include "Results.h"
#include "ReportUtils.h"
#include <cmath>

namespace zbench
{

struct ExperimentUtil
{
public:
	static constexpr double critical_val = 1.96;
	static constexpr double error_tolerance = 0.005;

	static void RunExperiment(const std::function<long long()>& trial, Result& result)
	{
		int num_samples = EstimateInitialISamplesNeeded(result, trial);
		do
		{
			result.sample_times.reserve((unsigned int)num_samples);
			for (int i = 0; i < num_samples; ++i)
				result.sample_times.push_back(trial());
		} while (NeedsMoreIterations(result, num_samples));
	}

private:
	static bool NeedsMoreIterations(const Result& result, int& iterations_needed)
	{
		const int num_trials = (int)result.sample_times.size();

		const ReportUtils::SampleStats stats = ReportUtils::GetSampleStats(result.sample_times);

		const double interval_width = critical_val * (stats.std_dev / sqrt((double)num_trials));

		if ((interval_width / stats.average) > error_tolerance)
		{
			iterations_needed = CalcNeededSamples(stats, num_trials);
			return true;
		}
		else
		{
			iterations_needed = 0;
			return false;
		}
	}

	static int EstimateInitialISamplesNeeded(Result& result, const std::function<long long()>& trial)
	{
		constexpr int num_trials = 1024;
		result.sample_times.reserve(num_trials);
		for (int i = 0; i < num_trials; ++i)
			result.sample_times.push_back(trial());

		const ReportUtils::SampleStats stats = ReportUtils::GetSampleStats(result.sample_times);

		return CalcNeededSamples(stats, (int)result.sample_times.size());
	}

	static int CalcNeededSamples(const ReportUtils::SampleStats & stats, const int num_samples)
	{
		const double sqrt_est_needed = (critical_val * stats.std_dev) / (error_tolerance * stats.average);
		const int est_needed = static_cast<int>(round(sqrt_est_needed * sqrt_est_needed));

		int runs_needed = 0;

		if (est_needed > num_samples)
			runs_needed = est_needed - num_samples;
		else
			runs_needed = est_needed / 10;

		if (runs_needed < 1)
			runs_needed = 1;

		return runs_needed;
	}
};

} // namespace zbench