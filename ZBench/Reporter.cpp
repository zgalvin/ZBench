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

} // namespace zbench