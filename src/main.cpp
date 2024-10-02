#include <ql/ql.hpp>
// #include <ql/graphic/graphic.hpp>

#include "fix-vcxproj.hpp"

int main()
try
{
	fix_vcxproj();
}
catch (const std::exception& any)
{
	ql::println("exception: ", any.what());
}