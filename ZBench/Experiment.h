#ifndef  EXPERIMENT_H
#define EXPERIMENT_H

#include "PlatformDefinitions.h"
WALL_WRN_PUSH
#include <chrono>
#include <vector>
#include <functional>
#include "Results.h"
#include "ExperimentUtil.h"
#include "Results.h"
#include "Timer.h"
WALL_WRN_POP

class SimpleExperiment;
template<typename FixT>
class FixtureExperiment;

class Experiment
{
public:
	Experiment() = default;
	~Experiment() = default;
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

	virtual void Run(Result & result) = 0;

};

class SimpleExperiment : public Experiment
{
private:
	// 	char pad[4]; // Padding for after base class
	std::function<void()> m_func;
	Timer timer;

public:
	SimpleExperiment(void(*func)()):
		m_func(std::function<void()>(func))
		// pad()
	{

	}
	virtual ~SimpleExperiment() = default;
	SimpleExperiment(const SimpleExperiment&) = delete;
	SimpleExperiment(SimpleExperiment&&) = delete;
	SimpleExperiment& operator= (const SimpleExperiment&) = delete;
	SimpleExperiment& operator= (SimpleExperiment&&) = delete;

	virtual void Run(Result & result)
	{
		auto const f = std::bind(&SimpleExperiment::RunTrial, this);
		ExperimentUtil::RunExperiment(f, result);
	}

	long long RunTrial()
	{
		//std::chrono::high_resolution_clock clock;
		//auto const tic = clock.now();
		//m_func();
		//auto const toc = clock.now();
		//return (toc - tic).count();
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
	{

	}
	virtual ~FixtureExperiment() = default;
	FixtureExperiment(const FixtureExperiment&) = delete;
	FixtureExperiment(FixtureExperiment&&) = delete;
	FixtureExperiment& operator= (const FixtureExperiment&) = delete;
	FixtureExperiment& operator= (FixtureExperiment&&) = delete;

	void Run(Result & result)
	{
		//auto f = [&] {return this->RunTrial(); };
		auto const f = std::bind(&FixtureExperiment::RunTrial, this);
		ExperimentUtil::RunExperiment(f, result);
	}

	long long RunTrial()
	{
		//m_fix.Setup();
		//auto const tic = clock.now();
		//m_func(m_fix);
		//auto const toc = clock.now();
		//m_fix.Teardown();
		//return (toc - tic).count();
		m_fix.Setup();
		timer.Tic();
		m_func();
		long long time = timer.Toc();
		m_fix.Teardown();
		return time;
	}
};


#endif // ! EXPERIMENT_H