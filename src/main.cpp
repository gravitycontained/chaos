#include <ql/ql.hpp>
// #include <ql/graphic/graphic.hpp>

#include "fix-vcxproj.hpp"

struct test
{
	std::string to_string() const
	{
		return "test";
	}
};

int main()
try
{
	constexpr auto tuple = ql::to_tuple(1, std::array{5, 6, 7}, 3, ql::to_tuple(4, 5, test{}), std::make_pair(4, "ok"));

	ql::recursive_value_apply(
			[](auto value, auto info)
			{ ql::println("depth: ", info.depth, ", first: ", info.first, ", last: ", info.last, ", value: ", value); }, tuple
	);

	ql::println(tuple);
	ql::println(ql::to_string(tuple));
}
catch (const std::exception& any)
{
	ql::println("exception: ", any.what());
}