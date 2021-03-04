#ifndef ZBENCH_OPTIONS_H
#define ZBENCH_OPTIONS_H

#include <stdio.h>
#include "Reporter.h"

struct ZBenchOptions
{
	Reporter::Type reporter_type;

	ZBenchOptions():
		reporter_type(Reporter::Type::Console)
	{

	}
};

#endif // !ZBENCH_OPTIONS_H
