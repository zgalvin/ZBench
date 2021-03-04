#include "Reporter.h"

std::shared_ptr<Reporter> Reporter::CreateReporter(const Type type)
{
	if (type == Type::Console)
		return std::make_shared<ConsoleReporter>();
	else if (type == Type::Json)
		return std::make_shared<JsonReporter>();

	// This shouldn't be what I do but let's default this way too
	return std::make_shared<ConsoleReporter>();
}
