#include "concurrency.h"

namespace le
{
	namespace concurrency
	{
		auto_thread::auto_thread()
			: thr(std::thread()), run_st(run_stat::RS_NULL)
		{}

		auto_thread::~auto_thread() noexcept
		{
			if (run_st == run_stat::RS_JOIN && thr.joinable())
			{
				try
				{
					thr.join();
				}
				catch (...)
				{
					;	//leave it alone
				}
			}
		}

		auto_thread::auto_thread(auto_thread && _Other)
			:thr(std::move(_Other.thr)), run_st(_Other.run_st)
		{}

		//shouldn't leave an auto_thread unjoined and assign a new one to it.
		//by thread's default behavior it'll terminate then let it terminate.
		auto_thread & auto_thread::operator=(auto_thread && _Other)
		{
			thr = std::move(_Other.thr);
			run_st = _Other.run_st;
		}

		std::thread::id auto_thread::get_id() const noexcept
		{
			return thr.get_id();
		}

		unsigned int auto_thread::hardware_concurrency() noexcept
		{
			return std::thread::hardware_concurrency();
		}

		void auto_thread::explicit_join()
		{
			try
			{
				thr.join();
			}
			catch (std::system_error const &se)
			{
				throw;
			}
		}

		mutex_base::mutex_base(mutex_base const & _Other) {}

		mutex_base::~mutex_base() {}

	}
}