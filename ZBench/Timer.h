#pragma once

#include "PlatformDefinitions.h"
WALL_WRN_PUSH
//#include <Windows.h>
#include <atomic>
#include <chrono>
WALL_WRN_POP

namespace zbench
{

class Timer
{
private:
	std::chrono::steady_clock timer;
	std::chrono::steady_clock::time_point tic;
	std::chrono::steady_clock::time_point toc;

	float TicksPerNano = 0.0f;
public:
	Timer() :
		timer(),
		tic(),
		toc()
	{
		//LARGE_INTEGER freq;
		//QueryPerformanceFrequency(&freq);
		//TicksPerNano = 1000000000.0f / static_cast<float>(freq.QuadPart);
		//constexpr auto my_period = (double)std::chrono::high_resolution_clock::period::num / (double)std::chrono::high_resolution_clock::period::den;
		//(my_period);
	}

	void Tic()
	{
		//atomic_thread_fence(std::memory_order_acq_rel);
		//QueryPerformanceCounter(&tic);
		//atomic_thread_fence(std::memory_order_acq_rel);
		tic = timer.now();
	}


	using Duration = decltype(toc - tic);
	Duration Toc()
	{
		//atomic_thread_fence(std::memory_order_acq_rel);
		//QueryPerformanceCounter(&toc);
		//atomic_thread_fence(std::memory_order_acq_rel);
		//return toc.QuadPart - tic.QuadPart;
		toc = timer.now();
		return toc - tic;
	}

	static auto ToNanoseconds(Duration time_stamp)
	{
		return std::chrono::nanoseconds(time_stamp).count();
	}
};

} // namspace zbench