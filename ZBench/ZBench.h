#pragma once

#include "BenchmarkRegistry.h"
#include "Bench.h"
#include "BenchImpls.h"
#include "ZBenchUtils.h"

#define ZBENCH_MAIN									\
int main(const int argc, const char* const argv[])	\
{													\
	const ZBenchOptions options = ParseArgs(argc, argv);	\
	BenchmarkRegistry::Run(options);				\
}

#define NAME_S(s) #s

#define BENCH(MyName, MyFunc) \
	void * MyName##_Test = BenchmarkRegistry::AddBench(NAME_S(MyName##_Test), MyFunc); 

//TODO: Static assert that args vec is args vec
#define BENCH_ARGS(MyName, MyFunc, ArgsVec) \
	void * MyName##_Test = BenchmarkRegistry::AddBench_A(NAME_S(MyName##_Test), MyFunc, ArgsVec);

//TODO: Static assert that fixture class is what is taken in by MyFunc
//TODO: Static asserts for setup and teardown functions
//TODO: Static assert that FixtureClass is default constructable?
#define BENCH_FIX(MyName, MyFunc, FixtureClass) \
	void * MyName##_Test = BenchmarkRegistry::AddBench_F(NAME_S(MyName##_Test), MyFunc);

//TODO: Static assert that args class, fixture class is what is taken in by MyFunc
//TODO: Static asserts for setup(arg) and teardown functions
//TODO: Static assert that FixtureClass is default constructable?
#define BENCH_ARGS_FIX(MyName, MyFunc, FixtureClass, ArgsVec) \
	void * MyName##_Test = BenchmarkRegistry::AddBench_AF(NAME_S(MyName##_Test), MyFunc, ArgsVec);