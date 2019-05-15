#include "MyCollectionParser.hpp"

std::vector<std::pair<std::string, int>> MyCollectionParser::get_cards(const std::string& filename) {
	std::vector<std::pair<std::string, int>> result;

	std::ifstream input(filename);
	std::string line;

	while (std::getline(input, line)) {
		std::string s = line.substr(0, line.length() - 2);
		int i = ctoi(line[line.length() - 1]);
		result.push_back(std::pair(s, i));
	}

	return result;
}
void MyCollectionParser::print_collection(const std::string& filename) {
	auto list = MyCollectionParser::get_cards(filename);
	for (auto p : list) {
		std::cout << p.first << " " << p.second << std::endl;
	}
}