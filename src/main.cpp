#include <ql/ql.hpp>

#include "fix-vcxproj.hpp"
#include "graphic.hpp"

#include <cmath>
#include <array>
#include <iomanip>
#include <iostream>
#include <string>


int main()
try
{
	// Test example usage
	//auto oklch = ql::oklch{0.6265, 0.2467, 30, 0.5};
	auto oklch = ql::oklch{ql::get_random_transparency_color()};

	ql::println("ql::oklch: ", oklch, " - ", oklch.as_rgba());

	graphic::run();
}
catch (const std::exception& any)
{
	ql::println("exception: ", any.what());
}