#ifndef BENCH_H
#define BENCH_H

#include <memory>
#include "Experiment.h"
#include "ArgsExperiment.h"
#include "Reporter.h"

class SimpleBench;
template<typename ArgT>
class ArgsBench;

class Bench
{
public:
	Bench() = delete;
	Bench(const Bench&) = delete;
	Bench(Bench&&) = delete;
	Bench& operator = (const Bench&) = delete;
	Bench& operator = (Bench&&) = delete;
	virtual ~Bench() = default;

	Bench(const char* name)	:
		m_name(name)
	{}

	virtual void RunTest(Reporter& reporter) = 0;
	virtual void Process(Reporter & reporter) = 0;

	const char* const GetName()
	{
		return m_name;
	}

	static std::shared_ptr<Bench> CreateBench(const char* name, void(*func)())
	{
		return std::static_pointer_cast<Bench>(std::make_shared<SimpleBench>(name, func));
	}

	template<typename FixT>
	static std::shared_ptr<Bench> CreateBench_F(const char* name, void(*func)(FixT&))
	{
		return std::make_shared<SimpleBench>(name, func);
	}

	template<typename ArgT>
	static std::shared_ptr<Bench> CreateBench_A(const char* name, void(*func)(const ArgT&), std::vector<ArgT>&& args_vec)
	{
		return std::make_shared<ArgsBench<ArgT>>(name, func, std::move(args_vec));
	}

	template<typename ArgT, typename FixT>
	static std::shared_ptr<Bench> CreateBench_AF(const char* name, void(*func)(const ArgT&, FixT&), std::vector<ArgT>&& args_vec)
	{
		return std::make_shared<ArgsBench<ArgT>>(name, func, std::move(args_vec));
	}

private:
	const char* m_name;
};

#endif