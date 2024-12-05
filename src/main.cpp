#include <ql/ql.hpp>

#include "fix-vcxproj.hpp"
#include "graphic.hpp"

#include "other/disc-analysis.hpp"

int main() try
{
	analyze_terminal();
	//graphic::run();
}
catch (const std::exception& any)
{
	ql::println("exception: ", any.what());
}