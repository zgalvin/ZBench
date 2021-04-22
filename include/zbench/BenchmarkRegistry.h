#pragma once

#include <vector>
#include <memory>
#include "BenchImpls.h"


namespace zbench
{

class Bench;
struct ExperimentArgs;
struct ZBenchOptions;

class BenchmarkRegistry
{
public:
	BenchmarkRegistry() = default;
	BenchmarkRegistry(const BenchmarkRegistry&) = delete;
	BenchmarkRegistry& operator = (const BenchmarkRegistry&) = delete;
	BenchmarkRegistry(BenchmarkRegistry&&) = delete;
	BenchmarkRegistry& operator = (BenchmarkRegistry&&) = delete;
	~BenchmarkRegistry() = default;

	static void Run(const ZBenchOptions& options);
	static void* AddBench(const char* name, void(*func)());

	static void Run(const ZBenchOptions& options, BenchmarkRegistry & registry);
	static void* AddBench(const char* name, void(*func)(), BenchmarkRegistry& registry);

	template<typename ArgT>
	static void* AddBench_A(const char* name, void(*func)(const ArgT&), std::vector<ArgT> args_vec)
	{
		return BenchmarkRegistry::AddBench_A(name, func, args_vec, getDefaultRegistry());
	}

	template<typename ArgT>
	static void* AddBench_A(const char* name, void(*func)(const ArgT&), std::vector<ArgT> args_vec, BenchmarkRegistry& registry)
	{
		registry.privAddBench_A(name, func, std::move(args_vec));
		return nullptr;
	}

	template<typename FixT>
	static void* AddBench_F(const char* name, void(*func)(FixT&))
	{
		return BenchmarkRegistry::AddBench_F(name, func, getDefaultRegistry());
	}

	template<typename FixT>
	static void* AddBench_F(const char* name, void(*func)(FixT&), BenchmarkRegistry& registry)
	{	
		registry.privAddBench_F(name, func);
		return nullptr;
	}

	template<typename ArgT, typename FixT>
	static void* AddBench_AF(const char* name, void(*func)(const ArgT&, FixT&), std::vector<ArgT> args_vec)
	{
		return BenchmarkRegistry::AddBench_AF(name, func, std::move(args_vec), getDefaultRegistry());;
	}

	template<typename ArgT, typename FixT>
	static void* AddBench_AF(const char* name, void(*func)(const ArgT&, FixT&), std::vector<ArgT> args_vec, BenchmarkRegistry & registry)
	{
		registry.privAddBench_AF(name, func, std::move(args_vec));
		return nullptr;
	}

private:
	static BenchmarkRegistry& getDefaultRegistry();
	void privAddBench(const char* name, void(*func)());

	template<typename FixT>
	void privAddBench_F(const char* name, void(*func)(FixT&))
	{
		m_benchmarks.push_back(CreateBench_F(name, func));
	}

	template<typename ArgT>
	void privAddBench_A(const char* name, void(*func)(const ArgT&), std::vector<ArgT>&& args_vec)
	{
		m_benchmarks.push_back(CreateBench_A(name, func, std::move(args_vec)));
	}

	template<typename ArgT, typename FixT>
	void privAddBench_AF(const char* name, void(*func)(const ArgT&, FixT&), std::vector<ArgT>&& args_vec)
	{
		m_benchmarks.push_back(CreateBench_AF(name, func, std::move(args_vec)));
	}

	void privRun(const ZBenchOptions& options);

	std::vector <std::unique_ptr<Bench>> m_benchmarks;
};

} // namespace zbench