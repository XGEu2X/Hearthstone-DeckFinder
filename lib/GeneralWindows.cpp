#include "GeneralWindows.hpp"

void read_directory(const std::string& name, std::vector<std::string>& List)
{
	std::filesystem::path p(name);
	std::filesystem::directory_iterator start(p);
	std::filesystem::directory_iterator end;
	std::transform(start, end, std::back_inserter(List), path_leaf_string());
}

bool download_file(const std::string& source, const std::string& path)
{
	HRESULT result = URLDownloadToFile(NULL, source.c_str(), path.c_str(), 0, NULL);
	return result == S_OK;
}

bool make_folder(const std::string& folderName, const std::string& path) {
	return _mkdir( (path+folderName).c_str() ) == 0;
}

bool remove_file(const std::string& filename, const std::string& path) {
	return remove((path + filename).c_str()) != -1;
}
