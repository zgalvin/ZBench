#pragma once

#include "PlatformDefinitions.h"
WALL_WRN_PUSH
#include <Windows.h>
#include <atomic>
#include <chrono>
WALL_WRN_POP

namespace zbench
{

class Timer
{
public:
	Timer() :
		tic(),
		toc(),
		pad()
	{
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);
		TicksPerNano = 1000000000.0f / static_cast<float>(freq.QuadPart);
		constexpr auto my_period = (double)std::chrono::high_resolution_clock::period::num / (double)std::chrono::high_resolution_clock::period::den;
		(my_period);
	}

	void Tic()
	{
		atomic_thread_fence(std::memory_order_acq_rel);
		QueryPerformanceCounter(&tic);
		atomic_thread_fence(std::memory_order_acq_rel);
	}

	long long Toc()
	{
		atomic_thread_fence(std::memory_order_acq_rel);
		QueryPerformanceCounter(&toc);
		atomic_thread_fence(std::memory_order_acq_rel);
		return toc.QuadPart - tic.QuadPart;
	}

	float ToNanoseconds(long long time_stamp)
	{
		return static_cast<float>(time_stamp) * TicksPerNano;
	}

private:
	LARGE_INTEGER tic;
	LARGE_INTEGER toc;

	float TicksPerNano = 0.0f;
	char pad[4];
};

} // namspace zbench