#ifndef CONCURRENCY_H__
#define CONCURRENCY_H__

#include "..\utility\utility.h"
#include <mutex>
#include <thread>
#include <type_traits>

using namespace le::utility;
namespace le
{
	namespace concurrency
	{
		//auto_managed thread object which can do join()/detach() behavior automaticly.
		//it can join-explicitly when necessary and then the auto end-up behavior won't be done.
		class auto_thread : private utility::uncopiable
		{
		public:
			static enum class run_stat { RS_JOIN, RS_DETACH, RS_NULL };
		
		private:
			std::thread thr;
			run_stat run_st;
		
		public:
			//generate a null thread waiting for job.
			auto_thread();

			template<class _Fn, class... _Args>
				explicit auto_thread(run_stat _Rs, _Fn&& _Fx, _Args&&... _Ax);

			~auto_thread() noexcept;

			//GIVE a job to it by MOVE a new rvalue to it
			auto_thread(auto_thread &&_Other);
			auto_thread &operator=(auto_thread &&_Other);

			std::thread::id get_id() const noexcept;

			static
			unsigned int hardware_concurrency() noexcept;

			//when the calling thread need it to modify a global variable, caller has to explicitly join it.
			void explicit_join() throw(std::system_error);
		};
		template<class _Fn, class ..._Args>
		inline auto_thread::auto_thread(run_stat _Rs, _Fn && _Fx, _Args && ..._Ax)
			:thr(std::thread(_Fx, _Ax...)), run_st(_Rs)
		{
			if (_Rs == run_stat::RS_DETACH) thr.detach();
		}

		//this is not for polymophicity.
		//this forces user to derive from it therefor no raw class without mutex's protect will be written,
		//and wrapper won't be wanted.
		class mutex_base
		{
		private:
			std::mutex mut;
		public:
			mutex_base() = default;

			mutex_base(mutex_base const &_Other);

			mutex_base &operator=(mutex_base const &_Other);

			~mutex_base() = default;
		};
	}
}

#endif // !CONCURRENCY_H__