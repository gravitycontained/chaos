#pragma once

#include <ql/ql.hpp>

void fix_vcxproj()
{
	ql::filesys::path path = "src/";
	auto list = path.list_current_directory_tree();

	std::vector<std::pair<std::string, bool>> mapped;
	for (auto& file : list)
	{
		if (file.is_directory())
			continue;

		auto string = file.string();
		auto isCpp = ql::string_ends_with(string, ".cpp");

		if (string != "src/main.cpp")
		{
			mapped.emplace_back(string, isCpp);
		}
	}

	ql::sort(mapped, [](const auto& a, const auto& b) { return ql::size_cast(a.second) > ql::size_cast(b.second); });


	std::string result = "\t<ItemGroup>\n";
	for (auto& i : mapped)
	{
		auto type = i.second ? "Compile" : "Include";
		result += ql::to_string("\t\t<Cl", type, " Include=\"", i.first, "\" />\n");
	}
	result += "\t</ItemGroup>";
	ql::copy_to_clipboard(result);

	ql::println(ql::bright_gray, "copied fixed vcxproj content with ", ql::aqua, ql::size_cast(mapped.size()), ql::bright_gray, " files to clipboard.");
}