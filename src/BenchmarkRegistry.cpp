#include <zbench/BenchmarkRegistry.h>

#include <zbench/PlatformDefinitions.h>
WALL_WRN_PUSH
#include <functional>
#include <zbench/Bench.h>
#include <zbench/BenchImpls.h>
#include <zbench/Experiment.h>
#include <zbench/Reporter.h>
#include <zbench/ZBenchOptions.h>
WALL_WRN_POP


namespace zbench
{

void BenchmarkRegistry::Run(const ZBenchOptions& options)
{
	BenchmarkRegistry::Run(options, getDefaultRegistry());
}

void* BenchmarkRegistry::AddBench(const char* name, void(*func)())
{
	return BenchmarkRegistry::AddBench(name, func, getDefaultRegistry());
}

void BenchmarkRegistry::Run(const ZBenchOptions& options, BenchmarkRegistry& registry)
{
	registry.privRun(options);
}

void* BenchmarkRegistry::AddBench(const char* name, void(*func)(), BenchmarkRegistry& registry)
{
	registry.privAddBench(name, func);
	return nullptr;
}

BenchmarkRegistry& BenchmarkRegistry::getDefaultRegistry()
{
	static BenchmarkRegistry instance;
	return instance;
}

void BenchmarkRegistry::privAddBench(const char* name, void(*func)())
{
	m_benchmarks.push_back(CreateBench(name, func));
}

void BenchmarkRegistry::privRun(const ZBenchOptions& options)
{
	std::unique_ptr<Reporter> reporter = Reporter::CreateReporter(options.reporter_type);
	reporter->BeginReport();
	for (auto& benchmark : m_benchmarks)
	{
		benchmark->RunTest(options.experiment_settings, *reporter);
	}
	reporter->EndReport();
}

} // namepspace zbench