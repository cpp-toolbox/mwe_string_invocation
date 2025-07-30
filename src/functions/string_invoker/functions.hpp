#ifndef STRING_INVOKER_FUNCTIONS_HPP
#define STRING_INVOKER_FUNCTIONS_HPP

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <string>
#include <optional>
#include "../../utility/meta_utils/meta_utils.hpp"
#include "../functions.hpp"

std::optional<std::string> invoke(std::string &invocation, std::vector<meta_utils::MetaType> available_types);
std::optional<int> add_string_invoker(std::string &input);
std::optional<std::string> add_string_invoker_to_string(std::string &input);

#endif // STRING_INVOKER_FUNCTIONS_HPP
