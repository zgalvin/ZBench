#include "Reporter.h"

namespace zbench
{

std::unique_ptr<Reporter> Reporter::CreateReporter(const Type type)
{
	std::unique_ptr<Reporter> retVal = std::make_unique<JsonReporter>();
	if (type == Type::Console)
		return std::make_unique<ConsoleReporter>();
	else if (type == Type::Json)
		return std::make_unique<JsonReporter>();

	// This shouldn't be what I do but let's default this way too
	return std::make_unique<ConsoleReporter>();
}

void ConsoleReporter::BeginReport()
{
	printf("%-*s%*s%*s%*s\n", 
		cellsize, "Name", 
		cellsize, "Avg. Time (ns)",
		cellsize, "Argument",
		cellsize, "# iterations");
}

void ConsoleReporter::ProcessResult(const Result& result)
{
	long long const average_time = ReportUtils::GetAverageTime(result.sample_times);
	printf("%-*s%*lld%*s%*u\n", 
		cellsize, result.test_name.c_str(), 
		cellsize, average_time, cellsize, 
		result.arg.c_str(), cellsize, 
		(unsigned int)result.sample_times.size());
}

void JsonReporter::BeginReport()
{
	printf("[\r\n");
	first = true;
}

void JsonReporter::ProcessResult(const Result& result)
{
	if (!first)
		printf("\t,\r\n");
	else
		first = false;

	const long long average_time = ReportUtils::GetAverageTime(result.sample_times);
	printf("\t{\r\n");
	printf("\t\t\"Test Name\": \"%s\",\r\n", result.test_name.c_str());
	printf("\t\t\"Arg\": \"%s\",\r\n", result.arg.c_str());
	printf("\t\t\"Avg. Time (ns)\": %lld,\r\n", average_time);
	printf("\t\t\"# iterations\": %u\r\n", (unsigned int)result.sample_times.size());
	printf("\t}\r\n");
}

void JsonReporter::EndReport()
{
	printf("]\r\n");
}

} // namespace zbench