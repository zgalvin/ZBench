#pragma once

#include "Reporter.h"
namespace zbench
{

struct ZBenchOptions
{
	Reporter::Type reporter_type;

	ZBenchOptions() :
		reporter_type(Reporter::Type::Console)
	{ }
};

} // namespace zbench