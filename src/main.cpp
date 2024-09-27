#include <ql/ql.hpp>
// #include <ql/maths/vector.hpp>

#include <iostream>

template <typename T>
  requires(ql::is_tuple<T>())
constexpr auto tuple_to_array(T tuple)
{
  std::array<ql::tuple_type<0, T>, ql::tuple_size<T>()> result{};
  auto unpack = [&]<typename Tuple, ql::size... Ints>(
                  Tuple tuple, std::index_sequence<Ints...>)
  {
    ((result[Ints]
      = ql::type_cast<ql::tuple_type<0, T>>(std::get<Ints>(tuple))),
     ...);
  };
  unpack(tuple, std::make_index_sequence<ql::tuple_size<T>()>());
  return result;
}

int main()
{
  constexpr auto size = 5;
  ql::constexpr_iterate<size>([](auto i) { ql::println("i : ", i); });

  constexpr auto x = ql::constexpr_apply<5>([](auto i) { return i.i; });

  ql::println();
}