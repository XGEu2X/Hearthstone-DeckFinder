#pragma once

#include <string>
#include <vector>
#include <filesystem>

//two parts function to list full names of files in an address
//function to list directories with its structure
struct path_leaf_string
{
	std::string operator()(const std::filesystem::directory_entry& entry) const
	{
		return entry.path().string();
	}
};
//fills a list with the full names of files in address
void read_directory(const std::string& address, std::vector<std::string>& List);