#include <ql/ql.hpp>

#include "fix-vcxproj.hpp"

int main()
try
{
	fix_vcxproj();

	using type = std::vector<std::pair<int, std::string>>;

	type values = {
			{1, "one"	 },
			{2, "two"	 },
			{3, "three"}
	};
	ql::apply_iterate(
			values, [](auto info, auto value)
			{ ql::println("depth: ", info.depth, ", first: ", info.first, ", last: ", info.last, ", value: ", value); }
	);
}
catch (const std::exception& any)
{
	ql::println("exception: ", any.what());
}