#pragma once

#include <string.h>
#include "ZBenchOptions.h"

namespace zbench
{

static bool StrMatches(const char* const str1, const char* const str2)
{
	return strcmp(str1, str2) == 0;
}

//static bool StrMatches(const char* const str1, const char* const str2, const char* const strs...)
//{
//	StrMatches(str1, str2);
//}

static ZBenchOptions ParseArgs(const int argc, const char* const argv[])
{
	ZBenchOptions options;

	for (int i = 0; i < argc; ++i)
	{
		if (StrMatches(argv[i], "--json"))
			options.reporter_type = Reporter::Type::Json;
		else if (StrMatches(argv[i], "--console"))
			options.reporter_type = Reporter::Type::Console;
	}

	return options;
}

} // namespace zbench