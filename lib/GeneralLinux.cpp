#include "GeneralLinux.hpp"

void read_directory(const std::string& address, std::vector<std::string>& List){
    DIR* dirp = opendir(address.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        List.push_back(address+dp->d_name);
    }
    closedir(dirp);
}
