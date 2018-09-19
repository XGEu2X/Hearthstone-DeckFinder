#include "GeneralWindows.hpp"

void read_directory(const std::string& name, std::vector<std::string>& List)
{
	std::filesystem::path p(name);
	std::filesystem::directory_iterator start(p);
	std::filesystem::directory_iterator end;
	std::transform(start, end, std::back_inserter(List), path_leaf_string());
}