#pragma once

#include <chrono>
#include <vector>
#include <functional>
#include "Results.h"
#include "ExperimentUtil.h"
#include "Results.h"
#include "Timer.h"

namespace zbench
{

class SimpleExperiment;
template<typename FixT>
class FixtureExperiment;

class Experiment
{
public:
	Experiment() = default;
	virtual ~Experiment() = default;
	Experiment(const Experiment&) = delete;
	Experiment(Experiment&&) = delete;
	Experiment& operator= (const Experiment&) = delete;
	Experiment& operator= (Experiment&&) = delete;

	static std::shared_ptr<Experiment> CreateExperiment(void(*func)())
	{
		auto ret = std::make_shared<SimpleExperiment>(func);
		return std::static_pointer_cast<Experiment>(ret);
	}

	template<typename FixT>
	static std::shared_ptr<Experiment> CreateExperiment_F(void(*func)(FixT&))
	{
		return std::make_shared<FixtureExperiment<FixT>>(func);
	}

	virtual Result Run(const ExperimentSettings& settings) = 0;

};

class SimpleExperiment : public Experiment
{
private:
	std::function<void()> m_func;
	Timer timer;
public:
	SimpleExperiment(void(*func)()) :
		m_func(std::function<void()>(func))
	{ }

	virtual ~SimpleExperiment() = default;
	SimpleExperiment(const SimpleExperiment&) = delete;
	SimpleExperiment(SimpleExperiment&&) = delete;
	SimpleExperiment& operator= (const SimpleExperiment&) = delete;
	SimpleExperiment& operator= (SimpleExperiment&&) = delete;

	virtual Result Run(const ExperimentSettings & settings) override
	{
		auto const f = std::bind(&SimpleExperiment::RunTrial, this);
		return ExperimentUtil::RunExperiment(f, settings);
	}

	Timer::Duration RunTrial()
	{
		timer.Tic();
		m_func();
		return timer.Toc();
	}
};

template<typename FixT>
class FixtureExperiment : public Experiment
{
private:
	FixT m_fix;
	std::function<void(FixT&)> m_func;
	Timer timer;
public:
	FixtureExperiment(void(*func)(FixT&)) :
		m_fix(),
		m_func(std::function<void(FixT&)>(func))
	{ }

	virtual ~FixtureExperiment() = default;
	FixtureExperiment(const FixtureExperiment&) = delete;
	FixtureExperiment(FixtureExperiment&&) = delete;
	FixtureExperiment& operator= (const FixtureExperiment&) = delete;
	FixtureExperiment& operator= (FixtureExperiment&&) = delete;

	virtual Result Run(const ExperimentSettings& settings) override
	{
		auto const f = std::bind(&FixtureExperiment::RunTrial, this);
		return ExperimentUtil::RunExperiment(f, settings);
	}

	Timer::Duration RunTrial()
	{
		m_fix.Setup();
		timer.Tic();
		m_func();
		long long time = timer.Toc();
		m_fix.Teardown();
		return time;
	}
};

} // namespace zbench