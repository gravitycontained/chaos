#include <ql/ql.hpp>
// #include <ql/maths/vector.hpp>

#include <iostream>

int main()
{
	constexpr auto x = ql::size_cast(5);
	constexpr auto tuple = ql::to_tuple(1, 2, 3, 4);
	constexpr auto a = ql::tuple_to_array(tuple);

	ql::println(a);
}