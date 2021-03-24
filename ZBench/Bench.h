#pragma once

#include <memory>
#include "Experiment.h"
#include "ArgsExperiment.h"
#include "Reporter.h"

namespace zbench
{

class Bench
{
public:
	Bench() = delete;
	Bench(const Bench&) = delete;
	Bench(Bench&&) = delete;
	Bench& operator = (const Bench&) = delete;
	Bench& operator = (Bench&&) = delete;
	virtual ~Bench() = default;

	Bench(const char* name) :
		m_name(name)
	{}

	virtual void RunTest(const ExperimentSettings& settings, Reporter& reporter) = 0;

	const std::string & GetName() const 
	{
		return m_name;
	}

protected:
	std::string m_name;
};

} // namespace zbench