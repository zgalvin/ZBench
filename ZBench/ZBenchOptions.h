#pragma once

#include "Reporter.h"
#include "ExperimentUtil.h"
namespace zbench
{

struct ZBenchOptions
{
	Reporter::Type reporter_type;
	ExperimentSettings experiment_settings;

	ZBenchOptions() :
		reporter_type(Reporter::Type::Console),
		experiment_settings()
	{ }
};

} // namespace zbench