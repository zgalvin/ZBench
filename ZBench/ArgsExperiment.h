#pragma once

#include <chrono>
#include <vector>
#include <functional>
#include "ExperimentUtil.h"

template<typename ArgT>
class SimpleArgsExperiment;
template<typename ArgT, typename FixT>
class FixtureArgsExperiment;

template<typename ArgT>
class ArgsExperiment
{
public:
	ArgsExperiment() = default;
	virtual ~ArgsExperiment() = default;
	ArgsExperiment(const ArgsExperiment&) = delete;
	ArgsExperiment(ArgsExperiment&&) = delete;
	ArgsExperiment& operator= (const ArgsExperiment&) = delete;
	ArgsExperiment& operator= (ArgsExperiment&&) = delete;

	static std::shared_ptr<ArgsExperiment> CreateExperiment(void(*func)(const ArgT&))
	{
		auto ret = std::make_shared<SimpleArgsExperiment<ArgT>>(func);
		return std::static_pointer_cast<ArgsExperiment>(ret);
	}

	template<typename FixT>
	static std::shared_ptr<ArgsExperiment> CreateExperiment_F(void(*func)(const ArgT&, FixT&))
	{
		return std::make_shared<FixtureArgsExperiment<ArgT,FixT>>(func);
	}

	virtual void Run(const ArgT& arg, Result & result) = 0;
};

template<typename ArgT>
class SimpleArgsExperiment : public ArgsExperiment<ArgT>
{
	std::function<void(const ArgT&)> m_func;
	Timer timer;
public:
	SimpleArgsExperiment(std::function<void(const ArgT&)> func) noexcept :
		m_func(std::function<void(const ArgT&)>(func))
	{

	}
	virtual ~SimpleArgsExperiment() = default;
	SimpleArgsExperiment(const SimpleArgsExperiment&) = delete;
	SimpleArgsExperiment(SimpleArgsExperiment&&) = delete;
	SimpleArgsExperiment& operator= (const SimpleArgsExperiment&) = delete;
	SimpleArgsExperiment& operator= (SimpleArgsExperiment&&) = delete;

	virtual void Run(const ArgT& arg, Result & result) override
	{
		auto f = std::bind(&SimpleArgsExperiment::RunTrial, this, arg);
		ExperimentUtil::RunExperiment(f, result);
	}

	long long RunTrial(const ArgT& arg)
	{
		timer.Tic();
		m_func(arg);
		return timer.Toc();
	}
};

template<typename ArgT, typename FixT>
class FixtureArgsExperiment : public ArgsExperiment<ArgT>
{
	FixT m_fix;
	std::function<void(const ArgT&, FixT&)> m_func;
	Timer timer;
public:
	FixtureArgsExperiment(std::function<void(const ArgT&, FixT&)> func) noexcept :
		m_fix(),
		m_func(std::function<void(const ArgT&, FixT&)>(func))
	{

	}
	virtual ~FixtureArgsExperiment() = default;
	FixtureArgsExperiment(const FixtureArgsExperiment&) = delete;
	FixtureArgsExperiment(FixtureArgsExperiment&&) = delete;
	FixtureArgsExperiment& operator= (const FixtureArgsExperiment&) = delete;
	FixtureArgsExperiment& operator= (FixtureArgsExperiment&&) = delete;

	virtual void Run(const ArgT& arg, Result & result) override
	{
		const auto f = std::bind(&FixtureArgsExperiment::RunTrial, this, arg);
		ExperimentUtil::RunExperiment(f, result);
	}

	long long RunTrial(const ArgT& arg)
	{
		m_fix.Setup(arg);
		timer.Tic();
		m_func(arg, m_fix);
		const long long time = timer.Toc();
		m_fix.Teardown();
		return time;
	}
};
