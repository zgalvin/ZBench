//#ifndef  TRIAL_H
//#define TRIAL_H
//
//#include <functional>
//
//class Trial
//{
//
//	virtual long long Run() = 0;
//};
//
//class SimpleTrial
//{
//	std::function<void()> m_func;
//public:
//	SimpleTrial(void(*func)()) :
//		m_func(std::function<void()>(func))
//	{
//
//	}
//	
//	virtual long long Run()
//	{
//		std::chrono::high_resolution_clock clock;
//		auto const tic = clock.now();
//		m_func();
//		auto const toc = clock.now();
//		return (toc - tic).count();
//	}
//};
//
//template<typename ArgT>
//class ArgsTrial
//{
//
//public:
//
//};
//
//#endif // ! TRIAL_H