#ifndef UTILITY_H__
#define UTILITY_H__

#include <functional>
#include <map>
#include <memory>
#include <typeindex>

namespace le
{
	namespace utility
	{
		class uncopiable
		{
		private:
			uncopiable(uncopiable const &);
			uncopiable &operator=(uncopiable const &);
		public:
			uncopiable() = default;
		};
	}
}

#endif // !UTILITY_H__
