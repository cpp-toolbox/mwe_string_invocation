#include "functions.hpp"
#include "../functions.hpp"
#include "../../utility/glm_utils/glm_utils.hpp"
#include "../../utility/glm_printing/glm_printing.hpp"
#include <regex>

std::optional<std::string> invoke(std::string &invocation, std::vector<meta_utils::MetaType> available_types) {
auto type_name_to_meta_type_map = meta_utils::create_type_name_to_meta_type_map(available_types);
    meta_utils::MetaFunctionSignature mfs_add("int add(int x, int y)", type_name_to_meta_type_map);

    if (std::regex_match(invocation, std::regex(mfs_add.invocation_regex))) {
        return add_string_invoker_to_string(invocation);
    }

    return "No matching function signature.";
}

std::optional<int> add_string_invoker(std::string &input) {
std::regex re(R"(^\s*add\s*\(\s*(-?\d+)\s*,\s*(-?\d+)\s*\)\s*$)");
    std::smatch match;
    if (!std::regex_match(input, match, re)) return std::nullopt;

    auto conversion1 = [](const std::string &s) { return std::stoi(s); };
    int x = conversion1(match[1]);
    auto conversion2 = [](const std::string &s) { return std::stoi(s); };
    int y = conversion2(match[2]);

    int result = add(x, y);
    return result;
}

std::optional<std::string> add_string_invoker_to_string(std::string &input) {
auto opt_result = add_string_invoker(input);
    if (!opt_result) return std::nullopt;
    auto conversion = [](const int &v) { return std::to_string(v); };
    return conversion(*opt_result);
}

