#include <ql/ql.hpp>

int main()
try
{
	ql::filesys::path path = "C:/dev/projects/C++/2024/QL/src/ql-core/ql";
	auto list = path.list_current_directory_tree();

	for (auto& i : list)
	{
		ql::println(i.string());
	}
}
catch (const std::exception& any)
{
	ql::println("Exception: ", any.what());
}