#pragma once

#include <string>
#include <vector>
#include <dirent.h>

//fills a list with full the names of files in address
void read_directory(const std::string& address, std::vector<std::string>& List);
