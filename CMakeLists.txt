cmake_minimum_required(VERSION 3.0.0)
project(ZBench
    VERSION 1.0
    DESCRIPTION "A simple microbenchmarking library."
    LANGUAGES CXX)


add_library(ZBench STATIC)
target_sources(ZBench PUBLIC 
	include/zbench/ArgsExperiment.h 
	include/zbench/ExperimentArgs.h 
	include/zbench/Results.h 
	include/zbench/ZBench.h 
	include/zbench/Bench.h 
	include/zbench/ExperimentUtil.h 
	include/zbench/RunExperiment.h 
	include/zbench/ZBenchOptions.h 
	include/zbench/BenchImpls.h 
	include/zbench/Fixture.h 
	include/zbench/StatUtils.h 
	include/zbench/ZBenchUtils.h 
	include/zbench/BenchmarkRegistry.h 
	include/zbench/PlatformDefinitions.h 
	include/zbench/Timer.h 
	include/zbench/Experiment.h 
	include/zbench/Reporter.h 
	include/zbench/Trial.h
)
target_sources(ZBench PRIVATE
	src/BenchmarkRegistry.cpp 
	src/Reporter.cpp
)

target_include_directories(ZBench PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)