#pragma once

#include "Reporter.h"

struct ZBenchOptions
{
	Reporter::Type reporter_type;

	ZBenchOptions():
		reporter_type(Reporter::Type::Console)
	{ }
};
