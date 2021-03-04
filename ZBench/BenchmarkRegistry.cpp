#include "BenchmarkRegistry.h"

#include "PlatformDefinitions.h"
WALL_WRN_PUSH
#include <functional>
#include "Bench.h"
#include "BenchImpls.h"
#include "Experiment.h"
#include "Reporter.h"
#include "ZBenchOptions.h"
WALL_WRN_POP


void BenchmarkRegistry::Run(const ZBenchOptions& options)
{
	BenchmarkRegistry& instance = Instance();
	instance.privRun(options);
}

void * BenchmarkRegistry::AddBench(const char* name, void(*func)())
{
	BenchmarkRegistry& instance = Instance();
	instance.privAddBench(name, func);
	return nullptr;
}

BenchmarkRegistry::BenchmarkRegistry()
	:m_benchmarks()
{

}

BenchmarkRegistry& BenchmarkRegistry::Instance()
{
	static BenchmarkRegistry instance;
	return instance;
}

void BenchmarkRegistry::privAddBench(const char* name, void(*func)())
{
	m_benchmarks.push_back(Bench::CreateBench(name, func));
}

void BenchmarkRegistry::privRun(const ZBenchOptions& options)
{
	std::shared_ptr<Reporter> reporter = Reporter::CreateReporter(options.reporter_type);
	reporter->BeginReport();
	for (auto benchmark : m_benchmarks)
	{
		//benchmark->RunTest(console_reporter);
		benchmark->RunTest(*reporter);
	}
	reporter->EndReport();
}
