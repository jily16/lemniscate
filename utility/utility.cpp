#include "utility.h"
#include <queue>

using std::queue;

namespace le
{
	namespace utility
	{
		using namespace std::experimental::filesystem;

		directory_iterator dir_end_it;

		bool is_dir(directory_entry const &_Entry)
		{
			return directory_iterator(_Entry) != dir_end_it;
		}

		directory_tree::directory_tree(std::string const & _Dir)
		{
			build_dir_tree(current_node, directory_entry(path(_Dir)));
		}

		void directory_tree::print(std::ostream & _Os) const
		{
			print_dir_tree(_Os, current_node, 0);
		}

		void directory_tree::build_dir_tree(
			std::shared_ptr<file_node>& _Node,
			directory_entry const & _Entry)
		{
			_Node = std::make_shared<file_node>(_Entry);
			if (is_dir(_Entry))
			{
				for (auto const &e : directory_iterator(_Entry))
				{
					_Node->next_layer.push_back(std::shared_ptr<file_node>());
					build_dir_tree(_Node->next_layer.back(), e);
				}
			}
		}
		void directory_tree::print_dir_tree(std::ostream & _Os, std::shared_ptr<file_node> _Node, std::size_t _Layer_count) const
		{
			for (size_t i = 0; i < _Layer_count; ++i) _Os << '\t';
			if (is_dir(_Node->entry))
			{
				_Os << '-';
			}
			_Os << _Node->entry.path() << std::endl;
			if (is_dir(_Node->entry))
			{
				for (auto node : _Node->next_layer)
				{
					print_dir_tree(_Os, node, _Layer_count + 1);
				}
			}
		}
	}
}