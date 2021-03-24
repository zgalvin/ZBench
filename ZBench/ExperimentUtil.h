#pragma once

#include <functional>
#include "Results.h"
#include "ReportUtils.h"
#include <cmath>

namespace zbench
{
	struct ExperimentSettings
	{
		double critical_val = 1.96;
		double error_tolerance = 0.005;
		unsigned int num_initial_samples = 1024u;
	};

struct ExperimentUtil
{
public:

	static void RunExperiment(const std::function<long long()>& trial, Result& result, const ExperimentSettings & settings)
	{
		unsigned int num_samples = settings.num_initial_samples;
		do
		{
			result.sample_times.reserve(num_samples);
			for (unsigned int i = 0; i < num_samples; ++i)
				result.sample_times.push_back(trial());
		} while (NeedMoreSamples(result, num_samples, settings));
	}

private:
	static bool NeedMoreSamples(const Result& result, unsigned int& iterations_needed, const ExperimentSettings& settings)
	{
		const int num_trials = (int)result.sample_times.size();

		const ReportUtils::SampleStats stats = ReportUtils::GetSampleStats(result.sample_times);

		const double interval_width = settings.critical_val * (stats.std_dev / sqrt((double)num_trials));

		if ((interval_width / stats.average) > settings.error_tolerance)
		{
			iterations_needed = CalcNeededSamples(stats, num_trials, settings);
			return true;
		}
		else
		{
			iterations_needed = 0;
			return false;
		}
	}

	static unsigned int CalcNeededSamples(const ReportUtils::SampleStats & stats, const unsigned int num_samples, const ExperimentSettings& settings)
	{
		const double sqrt_est_needed = (settings.critical_val * stats.std_dev) / (settings.error_tolerance * stats.average);
		const unsigned int est_needed = static_cast<int>(round(sqrt_est_needed * sqrt_est_needed));

		unsigned int runs_needed = 0;

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