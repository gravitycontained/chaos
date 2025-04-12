#include <ql/ql.hpp>

#include "fix-vcxproj.hpp"
#include "graphic.hpp"

int main() try
{
	graphic::run();
}
catch (const std::exception& any)
{
	ql::println("exception: ", any.what());
}