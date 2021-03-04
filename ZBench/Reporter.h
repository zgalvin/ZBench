#ifndef REPORTER_H
#define REPORTER_H

#include "PlatformDefinitions.h"
WALL_WRN_PUSH
#include <memory>
WALL_WRN_POP
#include "Results.h"
#include "ReportUtils.h"

class ConsoleReporter;
class JsonReporter;

class Reporter
{
public:
	virtual void BeginReport() {};
	virtual void ProcessResult(const Result& result) = 0;
	virtual void EndReport() {};

	enum class Type
	{
		Console,
		Json,
		Unknown
	};

	static std::shared_ptr<Reporter> CreateReporter(const Type type);
};

class ConsoleReporter : public Reporter
{
public:
	virtual void BeginReport() override
	{
		printf("%-*s%*s%*s\n", cellsize, "Name", cellsize, "Avg. Time (ns)", cellsize, "# iterations");
	}

	virtual void ProcessResult(const Result& result) override
	{
		long long const average_time = ReportUtils::GetAverageTime(result.sample_times);
		printf("%-*s%*lld%*s%*u\n", cellsize, result.test_name.c_str(), cellsize, average_time, cellsize, result.arg.c_str(), cellsize, (unsigned int)result.sample_times.size());
	}

private:
	const static int cellsize = 20;
};

class JsonReporter : public Reporter
{
public:
	virtual void BeginReport() override
	{
		printf("[\r\n");
	}

	virtual void ProcessResult(const Result& result) override
	{
		if (!first)
			printf("\t,\r\n");
		else
			first = false;

		long long const average_time = ReportUtils::GetAverageTime(result.sample_times);
		printf("\t{\r\n");
		printf("\t\t\"Test Name\": \"%s\",\r\n", result.test_name.c_str());
		printf("\t\t\"Arg\": \"%s\",\r\n", result.arg.c_str());
		printf("\t\t\"Avg. Time (ns)\": %lld,\r\n", average_time);
		printf("\t\t\"# iterations\": %u\r\n", (unsigned int)result.sample_times.size());
		printf("\t}\r\n");

		// printf("%-*s%*s%*s\n", cellsize, "Name", cellsize, "Avg. Time (ns)", cellsize, "# iterations");
		// printf("%-*s%*lld%*u\n", cellsize, result.name, cellsize, average_time, cellsize, (unsigned int)result.sample_times.size());
	}

	virtual void EndReport() override
	{
		printf("]\r\n");
	}

private:
	bool first = true;
	char pad[7] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
};

#endif // !REPORT_H

