#pragma once

#include <iostream>
#include <fstream>

#include "json.hpp"

nlohmann::json nlohmann_read_json(const std::string& filename);
