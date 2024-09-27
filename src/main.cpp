#include <ql/ql.hpp>
// #include <ql/maths/vector.hpp>

#include <iostream>

template <typename T>
requires (ql::is_container<T>())
constexpr void dbl(T& container)
{
	container >> [](int& i) { i *= 2; };
}

template <ql::size N>
constexpr auto create()
{
	std::array<int, N> arr = {1, 2, 3, 4};
	return arr >> [](int i) { return i *= 2; };
}

constexpr auto created = create<5>();

int main()
{
	constexpr auto tuple = ql::to_tuple(1, 2, 3, 4);

	constexpr auto size = ql::tuple_size<decltype(tuple)>();
	constexpr auto f =
			ql::constexpr_and_chain<size>([&](auto i) { return ql::is_printable<ql::tuple_type<i, decltype(tuple)>>(); });

	constexpr auto a = ql::tuple_to_array(tuple);

	constexpr auto vec = ql::vec(2, 3, 4);
	constexpr auto b = ql::has_to_string<decltype(vec)>();

	ql::hitbox h;

	ql::println(a, " and ", h);

	constexpr auto x = ql::is_printable<decltype(tuple)>();

	auto fun = []() { return 0; };

	using ret_type = ql::return_type<decltype(fun)>;
	ql::println(ql::return_size<decltype(fun)>());

	std::array<int, 4> arr = {1, 2, 3, 4};
	dbl(arr);
	ql::println("arra: ", arr);
}