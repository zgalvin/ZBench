#include "PlatformDefinitions.h"
WALL_WRN_PUSH
#include <chrono>
#include <random>
#include "ZBench.h"
WALL_WRN_POP

ZBENCH_MAIN

class SortFixture
{
public:

	SortFixture() {}

	void Setup(const size_t& arg)
	{
		data.resize(arg, 0);
		for (unsigned int i = 0; i < data.size(); ++i)
		{
			data[i] = std::rand();
		}
	}

	void Teardown() {}

	std::vector<int> data;
};

void my_function(const size_t&, SortFixture& fix)
{
	std::sort(fix.data.begin(), fix.data.end());
}


void bubble_sort(const size_t& arg, SortFixture& fix)
{

	for (unsigned int x = 0; x < arg; x++)
	{
		for (unsigned int y = 0; y < arg - 1; y++)
		{
			if (fix.data[y] > fix.data[(size_t)y + 1])
			{
				std::swap(fix.data[y], fix.data[(size_t)y + 1]);
			}
		}
	}
}

void select_sort(const size_t& arg, SortFixture& fix)
{
	for (unsigned int x = 0; x < arg; x++)
	{
		auto minIdx = x;

		for (unsigned int y = x; y < arg; y++)
		{
			if (fix.data[minIdx] > fix.data[y])
			{
				minIdx = y;
			}
		}

		std::swap(fix.data[x], fix.data[minIdx]);
	}
}

// http://www.bfilipek.com/2014/12/top-5-beautiful-c-std-algorithms.html
void insert_sort(const size_t&, SortFixture& fix)
{
	for (auto i = std::begin(fix.data); i != std::end(fix.data); ++i)
	{
		std::rotate(std::upper_bound(std::begin(fix.data), i, *i), i, std::next(i));
	}
}

// http://www.bfilipek.com/2014/12/top-5-beautiful-c-std-algorithms.html
template <typename FwdIt, typename Compare = std::less<typename FwdIt::value_type>>
void QuickSort(FwdIt first, FwdIt last, Compare cmp = Compare{})
{
	auto const N = std::distance(first, last);

	if (N <= 1)
	{
		return;
	}

	auto const pivot = std::next(first, N / 2);
	std::nth_element(first, pivot, last, cmp);
	QuickSort(first, pivot, cmp);
	QuickSort(pivot, last, cmp);
}

void quick_sort(const size_t&, SortFixture& fix)
{
	QuickSort(std::begin(fix.data), std::end(fix.data));
}

void std_sort(const size_t&, SortFixture& fix)
{
	std::sort(std::begin(fix.data), std::end(fix.data), std::less<int64_t>());
}


std::vector<size_t> my_args = { 64, 128, 256, 512 };// , 1024, 2048, 4096 };

//BENCH_ARGS_FIX(BubbleSort, bubble_sort, MyFixture, my_args)
//BENCH_ARGS_FIX(SelectSort, select_sort, MyFixture, my_args);
//BENCH_ARGS_FIX(InsertSort, insert_sort, MyFixture, my_args);
//BENCH_ARGS_FIX(QuickSort, quick_sort, MyFixture, my_args);
BENCH_ARGS_FIX(StdSort, std_sort, MyFixture, my_args);