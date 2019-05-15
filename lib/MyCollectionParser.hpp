#pragma once

#include "General.hpp"

#include <iostream>
#include <string>
#include <fstream>

namespace MyCollectionParser {
	std::vector<std::pair<std::string, int>> get_cards(const std::string& filename);
	void print_collection(const std::string& filename);
}