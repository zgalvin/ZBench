#ifndef EXPERIMENT_REGISTRY_H
#define EXPERIMENT_REGISTRY_H

#include "PlatformDefinitions.h"
WALL_WRN_PUSH
#include <vector>
#include <memory>
WALL_WRN_POP

class Bench;
struct ExperimentArgs;
struct ZBenchOptions;

class BenchmarkRegistry
{
public:
	BenchmarkRegistry(const BenchmarkRegistry&) = delete;
	BenchmarkRegistry(BenchmarkRegistry&&) = delete;
	BenchmarkRegistry& operator = (const BenchmarkRegistry&) = delete;
	BenchmarkRegistry& operator = (BenchmarkRegistry&&) = delete;
	~BenchmarkRegistry() = default;

	static void Run(const ZBenchOptions & options);
	static void* AddBench(const char* name, void(*func)());

	template<typename ArgT>
	static void* AddBench_A(const char* name, void(*func)(const ArgT&), std::vector<ArgT> args_vec)
	{
		BenchmarkRegistry& instance = Instance();
		instance.privAddBench_A(name, func, std::move(args_vec));
		return nullptr;
	}

	template<typename FixT>
	static void* AddBench_F(const char* name, void(*func)(FixT&))
	{
		BenchmarkRegistry& instance = Instance();
		instance.privAddBench_F(name, func);
		return nullptr;
	}

	template<typename ArgT, typename FixT>
	static void* AddBench_AF(const char* name, void(*func)(const ArgT&, FixT&), std::vector<ArgT> args_vec)
	{
		BenchmarkRegistry& instance = Instance();
		instance.privAddBench_AF(name, func, std::move(args_vec));
		return nullptr;
	}

private:
	BenchmarkRegistry();
	static BenchmarkRegistry& Instance();
	void privAddBench(const char* name, void(*func)());

	template<typename FixT>
	void privAddBench_F(const char* name, void(*func)(FixT&))
	{
		m_benchmarks.push_back(Bench::CreateBench_F(name, func));
	}

	template<typename ArgT>
	void privAddBench_A(const char* name, void(*func)(const ArgT&), std::vector<ArgT>&& args_vec)
	{
		m_benchmarks.push_back(Bench::CreateBench_A(name, func, std::move(args_vec)));
	}

	template<typename ArgT, typename FixT>
	void privAddBench_AF(const char* name, void(*func)(const ArgT&, FixT&), std::vector<ArgT>&& args_vec)
	{
		m_benchmarks.push_back(Bench::CreateBench_AF(name, func, std::move(args_vec)));
	}

	void privRun(const ZBenchOptions& options);

	std::vector <std::shared_ptr<Bench>> m_benchmarks;
};

#endif