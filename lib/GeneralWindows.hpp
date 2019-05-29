#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

#include <urlmon.h>
#include <direct.h>
#pragma comment(lib, "urlmon.lib")

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

//download a file
bool download_file(const std::string& source, const std::string& path = "");

//make a folder
bool make_folder(const std::string& folderName, const std::string& path = "");

//remove a file
bool remove_file(const std::string& filename, const std::string& path = "");