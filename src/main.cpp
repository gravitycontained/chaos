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

	ql::println(tuple);

	ql::recursive_value_apply([](auto value) { ql::println(", value: ", value); }, tuple);

	//constexpr auto count = ql::constexpr_apply<ql::tuple_size<decltype(tuple)>()>(
	//		[&](auto index)
	//		{
	//			ql::println("index: ", index.i, ", value: ", ql::tuple_value<index>(tuple));
	//			//return index.i;
	//		}
	//);
	ql::constexpr_iterate<ql::tuple_size<decltype(tuple)>()>(
			[&](auto index)
			{
				auto&& i = ql::tuple_value<index>(std::forward<decltype(tuple)>(tuple));
				ql::println("index: ", index.i, ", value: ", ql::tuple_value<index>(tuple));
			}
	);
}
catch (const std::exception& any)
{
	ql::println("exception: ", any.what());
}