#pragma once

#include <memory>
#include "Results.h"
#include "StatUtils.h"

namespace zbench
{

class Reporter
{
public:
	virtual void BeginReport() {};
	virtual void ProcessResult(const ExperimentInfo& info, const Result& result) = 0;
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
	virtual void ProcessResult(const ExperimentInfo& info, const Result& result) override;

private:
	const static int cellsize = 20;
};

class JsonReporter : public Reporter
{
public:
	virtual void BeginReport() override;
	virtual void ProcessResult(const ExperimentInfo& info, const Result& result) override;
	virtual void EndReport() override;

private:
	bool first = true;
};

} // namespace zbench