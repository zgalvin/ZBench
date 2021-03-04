#pragma once

#include <functional>
#include "Results.h"
#include "ReportUtils.h"
#include <cmath>

struct ExperimentUtil
{
public:
	static constexpr double critical_val = 1.96;
	static constexpr double error_tolerance = 0.005;

	static void RunExperiment(const std::function<long long()>& trial, Result& result)
	{
		int num_samples = GetIterationsNeeded(result, trial);
		do
		{
			result.sample_times.reserve((unsigned int)num_samples);
			for (int i = 0; i < num_samples; ++i)
			{
				result.sample_times.push_back(trial());
			}
		} while (NeedsMoreIterations(result, num_samples));
	}

	static bool NeedsMoreIterations(const Result& result, int & iterations_needed)
	{
		int num_trials = (int)result.sample_times.size();
		double sample_std_dev;
		double sample_avg;
		ReportUtils::GetSampleStdDev(result.sample_times, sample_std_dev, sample_avg);

		double interval_width = critical_val * (sample_std_dev / sqrt((double)num_trials));

		if ((interval_width / sample_avg) > error_tolerance)
		{
			iterations_needed = CalcNeededRuns(sample_std_dev, sample_avg, num_trials);
			return true;
		}
		else
		{
			iterations_needed = 0;
			return false;
		}
	}

private:
	static int GetIterationsNeeded(Result& result, const std::function<long long()>& trial)
	{
		//std::vector<long long> initial_times;
		const int num_trials = 1024;
		result.sample_times.reserve(num_trials);
		for (int i = 0; i < num_trials; ++i)
		{
			result.sample_times.push_back(trial());
		}

		double sample_std_dev;
		double sample_avg;
		ReportUtils::GetSampleStdDev(result.sample_times, sample_std_dev, sample_avg);

		return CalcNeededRuns(sample_std_dev, sample_avg, (int)result.sample_times.size());
	}

	static int CalcNeededRuns(const double & sample_std_dev, const double & sample_avg, const int num_initial_runs)
	{
		const double sqrt_est_needed = (critical_val * sample_std_dev) / (error_tolerance * sample_avg);
		const int est_needed = (int)round(sqrt_est_needed * sqrt_est_needed);

		int runs_needed = 0;

		if (est_needed > (int)num_initial_runs)
			runs_needed = est_needed - (int)num_initial_runs;
		else
			runs_needed = est_needed / 10;

		if (runs_needed < 1)
			runs_needed = 1;

		return runs_needed;
	}
};