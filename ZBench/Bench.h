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

	virtual void RunTest(Reporter& reporter) = 0;
	virtual void Process(Reporter& reporter) = 0;

	const char* const GetName()
	{
		return m_name;
	}

private:
	const char* m_name;
};

} // namespace zbench