#include <ql/ql.hpp>
#include <iostream>

int main()
{
  constexpr auto size = 5;
  ql::constexpr_iterate<size>([](auto i) { ql::println("i : ", i); });

  constexpr auto x = ql::constexpr_apply<5>([](auto i) { return i.i; });

  ql::println();
}