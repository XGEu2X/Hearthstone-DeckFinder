#include "NlohmannjsonUtils.hpp"

nlohmann::json nlohmann_read_json(const std::string& filename)
{
    std::ifstream f(filename);
    nlohmann::json j;
    f >> j;
    return j;
}
