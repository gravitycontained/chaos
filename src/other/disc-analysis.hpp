#pragma once

#include <ql/ql.hpp>

ql::size file_size_recursive(const ql::filesys::path& path)
{
	try
	{
		return path.file_size_recursive();
	}
	catch (const std::exception& any)
	{
		ql::println("exception: ", any.what());
	}
	return 0ull;
}

void ls(ql::filesys::path path)
{
	std::vector<std::pair<ql::filesys::path, ql::size>> files;

	for (const auto& entry : path.list_current_directory())
	{
		auto size = file_size_recursive(entry);

		files.push_back({entry, size});
	}

	ql::sort(files, [](const auto& a, const auto& b) { return a.second > b.second; });

	auto max_length = 0ull;

	for (const auto& [name, size] : files)
	{
		max_length = ql::max(max_length, name.to_string().length());
	}

	for (const auto& [name, size] : files)
	{
		
		ql::println(ql::color::bright_gray, ql::string_appended(name, ' ', max_length), " :: ", ql::color::aqua, ql::string_memory_size(size));
	}
}

void analyze_terminal()
{
	auto path = ql::filesys::get_current_location();
	ql::println(
			ql::color::bright_gray, "commands: ", ql::color::aqua, "ls", ql::color::bright_gray, ", ", ql::color::aqua, "cd",
			ql::color::bright_gray,
			", ", ql::color::aqua, "exit"
	);

	while (true)
	{
		ql::print('\n', ql::color::bright_gray, path.to_string(), " > ", ql::color::aqua);
		auto input = ql::get_input();

		auto split = ql::string_split(input, ' ');

		if (split.empty())
			continue;

		auto command = split[0];

		if (command == "ls")
		{
			ls(path);
		}
		else if (command == "cd" && split.size() > 1)
		{
			auto new_path = split[1];

			if (new_path == "..")
			{
				path = path.get_parent_branch();
			}
			else
			{
				path = path.go_into(new_path);
			}
		}
		else if (command == "exit")
		{
			break;
		}
		else
		{
			ql::println(ql::color::bright_gray, "unknown command: ", ql::color::aqua, command);
		}
	}
}
