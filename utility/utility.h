#ifndef UTILITY_H__
#define UTILITY_H__

#include <filesystem>
#include <iostream>		//for ostream
#include <memory>		//for shared_ptr
#include <string>
#include <vector>

using namespace std::experimental::filesystem;

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

		class directory_tree
		{
		public:
			explicit directory_tree(std::string const &_Dir);

			void print(std::ostream &_Os) const;
			
		private:
			struct file_node
			{
				directory_entry entry;
				std::vector<std::shared_ptr<file_node>> next_layer;
				file_node(directory_entry const &_Entry) :entry(_Entry) {}
			};

			std::shared_ptr<file_node> current_node;

			void build_dir_tree(std::shared_ptr<file_node> &_Node, directory_entry const &_Entry);

			void print_dir_tree(std::ostream &_Os,
				std::shared_ptr<file_node> _Node,
				std::size_t _Layer_count) const;
		};
	}
}

#endif // !UTILITY_H__
