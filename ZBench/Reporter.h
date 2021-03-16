#pragma once

#include "PlatformDefinitions.h"
WALL_WRN_PUSH
#include <memory>
WALL_WRN_POP
#include "Results.h"
#include "ReportUtils.h"

namespace zbench
{

class Reporter
{
public:
	virtual void BeginReport() {};
	virtual void ProcessResult(const Result& result) = 0;
	virtual void EndReport() {};
	virtual ~Reporter() = default;

	enum class Type
	{
		Console,
		Json,
		Unknown
	};

	static std::unique_ptr<Reporter> CreateReporter(const Type type);
};

class ConsoleReporter : public Reporter
{
public:
	virtual void BeginReport() override;
	virtual void ProcessResult(const Result& result) override;

private:
	const static int cellsize = 20;
};

class JsonReporter : public Reporter
{
public:
	virtual void BeginReport() override;
	virtual void ProcessResult(const Result& result) override;
	virtual void EndReport() override;

private:
	bool first = true;
	char pad[7] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
};

} // namespace zbench