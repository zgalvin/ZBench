#pragma once

#include <chrono>
#include <vector>
#include <functional>
#include "ExperimentUtil.h"


namespace zbench
{

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

	static std::unique_ptr<ArgsExperiment> CreateExperiment(void(*func)(const ArgT&))
	{
		return std::make_unique<SimpleArgsExperiment<ArgT>>(func);
	}

	template<typename FixT>
	static std::unique_ptr<ArgsExperiment> CreateExperiment_F(void(*func)(const ArgT&, FixT&))
	{
		return std::make_unique<FixtureArgsExperiment<ArgT, FixT>>(func);
	}

	virtual Result Run(const ExperimentSettings& settings, const ArgT& arg) = 0;
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

	virtual Result Run(const ExperimentSettings& settings, const ArgT& arg) override
	{
		auto f = std::bind(&SimpleArgsExperiment::RunTrial, this, arg);
		return ExperimentUtil::RunExperiment(f, settings);
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

	virtual Result Run(const ExperimentSettings& settings, const ArgT& arg) override
	{
		const auto f = std::bind(&FixtureArgsExperiment::RunTrial, this, arg);
		return ExperimentUtil::RunExperiment(f, settings);
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

} // namespace zbench