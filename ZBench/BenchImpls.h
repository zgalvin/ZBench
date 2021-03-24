#pragma once

#include "Bench.h"
#include "Results.h"
#include <sstream>

namespace zbench
{

class SimpleBench : public Bench
{
private:
	std::shared_ptr<Experiment> m_exp;
public:
	SimpleBench(const char* name, void(*func)())
		:Bench(name),
		m_exp(Experiment::CreateExperiment(func))
	{ }

	template<typename FixT>
	SimpleBench(const char* name, void(*func)(FixT&))
		: Bench(name),
		m_exp(Experiment::CreateExperiment_F(func))
	{ }

	virtual void RunTest(const ExperimentSettings& settings, Reporter& reporter) override
	{
		ExperimentInfo info(m_name);
		Result result = m_exp->Run(settings);
		reporter.ProcessResult(info, result);
	}

	SimpleBench(const SimpleBench&) = delete;
	SimpleBench(SimpleBench&&) = delete;
	SimpleBench& operator = (const SimpleBench&) = delete;
	SimpleBench& operator = (SimpleBench&&) = delete;
	virtual ~SimpleBench() = default;
};

static std::unique_ptr<Bench> CreateBench(const char* name, void(*func)())
{
	return std::make_unique<SimpleBench>(name, func);
}

template<typename FixT>
static std::unique_ptr<Bench> CreateBench_F(const char* name, void(*func)(FixT&))
{
	return std::make_unique<SimpleBench>(name, func);
}

template<typename ArgT>
class ArgsBench : public Bench
{
public:
	ArgsBench(const char* name, void(*func)(const ArgT&), std::vector<ArgT>&& args_vec)
		:Bench(name),
		m_exp(ArgsExperiment<ArgT>::CreateExperiment(func)),
		m_args(std::move(args_vec))
	{	}

	template<typename FixT>
	ArgsBench(const char* name, void(*func)(const ArgT&, FixT&), std::vector<ArgT>&& args_vec)
		:Bench(name),
		m_exp(ArgsExperiment<ArgT>::CreateExperiment_F(func)),
		m_args(std::move(args_vec))
	{	}

	virtual void RunTest(const ExperimentSettings& settings, Reporter& reporter) override
	{
		ExperimentInfo info(GetName());
		for (auto arg : m_args)
		{
			std::ostringstream os;
			os << arg;

			info.arg = os.str();
			Result result = m_exp->Run(settings, arg);
			reporter.ProcessResult(info, result);
		}
	}

	ArgsBench(const ArgsBench&) = delete;
	ArgsBench(ArgsBench&&) = delete;
	ArgsBench& operator = (const ArgsBench&) = delete;
	ArgsBench& operator = (ArgsBench&&) = delete;
	virtual ~ArgsBench() = default;
private:
	std::shared_ptr<ArgsExperiment<ArgT>> m_exp;
	std::vector <ArgT> m_args;
};

template<typename ArgT>
static std::unique_ptr<Bench> CreateBench_A(const char* name, void(*func)(const ArgT&), std::vector<ArgT>&& args_vec)
{
	return std::make_unique<ArgsBench<ArgT>>(name, func, std::move(args_vec));
}

template<typename ArgT, typename FixT>
static std::unique_ptr<Bench> CreateBench_AF(const char* name, void(*func)(const ArgT&, FixT&), std::vector<ArgT>&& args_vec)
{
	return std::make_unique<ArgsBench<ArgT>>(name, func, std::move(args_vec));
}


} // namespace zbench