#pragma once

#include "Bench.h"
#include "Results.h"
#include <sstream>

class SimpleBench : public Bench
{
public:
	SimpleBench(const char* name, void(*func)())
		:Bench(name),
		m_exp(Experiment::CreateExperiment(func)),
		m_result(name)
	{
	}

	template<typename FixT>
	SimpleBench(const char* name, void(*func)(FixT&))
		:Bench(name),
		m_exp(Experiment::CreateExperiment_F(func)),
		m_result(name)
	{
	}

	virtual void RunTest(Reporter& reporter) override
	{
		m_exp->Run(m_result);
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
	// std::vector<long long> m_sampleTimes;
	Result m_result;
};

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

	virtual void RunTest(Reporter& reporter) override
	{
		for (auto arg : m_args)
		{
			std::ostringstream os;
			os << arg;

			Result result(GetName(), os.str().c_str());
			m_exp->Run(arg, result);
			reporter.ProcessResult(result);
			m_results.push_back(std::move(result));
		}
	}

	virtual void Process(Reporter& reporter) override
	{
		for (Result & result : m_results)
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