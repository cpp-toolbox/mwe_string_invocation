#ifndef STRING_INVOKER_FUNCTIONS_HPP
#define STRING_INVOKER_FUNCTIONS_HPP

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <string>
#include <optional>
#include "../../utility/meta_utils/meta_utils.hpp"

std::optional<std::string> invoke(std::string &invocation, std::vector<meta_utils::MetaType> available_types);
std::optional<std::string> add_string_invoker(std::string &input);
std::optional<std::string> mul_string_invoker(std::string &input);
std::optional<std::string> mul_vec_string_invoker(std::string &input);
std::optional<std::string> sum_string_invoker(std::string &input);
std::optional<std::string> sum_vec_string_invoker(std::string &input);
std::optional<std::string> vec_to_force_string_invoker(std::string &input);
std::optional<std::string> force_to_vec_string_invoker(std::string &input);
std::optional<std::string> force_to_string_string_invoker(std::string &input);
std::optional<std::string> string_to_force_string_invoker(std::string &input);

#endif // STRING_INVOKER_FUNCTIONS_HPP
