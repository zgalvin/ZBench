#pragma once

#include "Bench.h"
#include "Results.h"
#include <sstream>

namespace zbench
{

class SimpleBench : public Bench
{
public:
	SimpleBench(const char* name, void(*func)())
		:Bench(name),
		m_exp(Experiment::CreateExperiment(func)),
		m_result(name)
	{ }

	template<typename FixT>
	SimpleBench(const char* name, void(*func)(FixT&))
		: Bench(name),
		m_exp(Experiment::CreateExperiment_F(func)),
		m_result(name)
	{ }

	virtual void RunTest(const ExperimentSettings& settings, Reporter& reporter) override
	{
		m_exp->Run(settings, m_result);
		reporter.ProcessResult(m_result);
	}

	virtual void Process(Reporter& reporter) override
	{
		reporter.ProcessResult(m_result);
	}

	SimpleBench(const SimpleBench&) = delete;
	SimpleBench(SimpleBench&&) = delete;
	SimpleBench& operator = (const SimpleBench&) = delete;
	SimpleBench& operator = (SimpleBench&&) = delete;
	virtual ~SimpleBench() = default;
private:
	std::shared_ptr<Experiment> m_exp;
	Result m_result;
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
	{
		m_results.reserve(m_args.size());
	}

	template<typename FixT>
	ArgsBench(const char* name, void(*func)(const ArgT&, FixT&), std::vector<ArgT>&& args_vec)
		:Bench(name),
		m_exp(ArgsExperiment<ArgT>::CreateExperiment_F(func)),
		m_args(std::move(args_vec))
	{
		m_results.reserve(m_args.size());
	}

	virtual void RunTest(const ExperimentSettings& settings, Reporter& reporter) override
	{
		for (auto arg : m_args)
		{
			std::ostringstream os;
			os << arg;

			Result result(GetName(), os.str());
			m_exp->Run(settings, arg, result);
			reporter.ProcessResult(result);
			m_results.push_back(std::move(result));
		}
	}

	virtual void Process(Reporter& reporter) override
	{
		for (const Result& result : m_results)
		{
			reporter.ProcessResult(result);
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
	std::vector<Result> m_results;
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