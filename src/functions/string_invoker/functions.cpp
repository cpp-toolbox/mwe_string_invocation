#include "functions.hpp"
#include "../functions.hpp"
#include "../../utility/glm_utils/glm_utils.hpp"
#include "../../utility/glm_printing/glm_printing.hpp"
#include <regex>

std::optional<std::string> invoke(std::string &invocation, std::vector<meta_utils::MetaType> available_types) {
auto type_name_to_meta_type_map = meta_utils::create_type_name_to_meta_type_map(available_types);
    meta_utils::MetaFunctionSignature mfs_add("int add(int x, int y)", type_name_to_meta_type_map);
    meta_utils::MetaFunctionSignature mfs_mul("int mul(int x, int y)", type_name_to_meta_type_map);
    meta_utils::MetaFunctionSignature mfs_mul_vec("glm::vec3 mul_vec(glm::vec3 v, float c)", type_name_to_meta_type_map);
    meta_utils::MetaFunctionSignature mfs_sum("float sum(std::vector<float> nums)", type_name_to_meta_type_map);
    meta_utils::MetaFunctionSignature mfs_sum_vec("glm::vec3 sum_vec(std::vector<glm::vec3> vecs)", type_name_to_meta_type_map);
    meta_utils::MetaFunctionSignature mfs_vec_to_force("Force vec_to_force(glm::vec3 v)", type_name_to_meta_type_map);
    meta_utils::MetaFunctionSignature mfs_force_to_vec("glm::vec3 force_to_vec(Force f)", type_name_to_meta_type_map);
    meta_utils::MetaFunctionSignature mfs_force_to_string("std::string force_to_string(Force f)", type_name_to_meta_type_map);
    meta_utils::MetaFunctionSignature mfs_string_to_force("Force string_to_force(std::string s)", type_name_to_meta_type_map);

    if (std::regex_match(invocation, std::regex(mfs_add.invocation_regex))) {
        return add_string_invoker_to_string(invocation);
    }
    if (std::regex_match(invocation, std::regex(mfs_mul.invocation_regex))) {
        return mul_string_invoker_to_string(invocation);
    }
    if (std::regex_match(invocation, std::regex(mfs_mul_vec.invocation_regex))) {
        return mul_vec_string_invoker_to_string(invocation);
    }
    if (std::regex_match(invocation, std::regex(mfs_sum.invocation_regex))) {
        return sum_string_invoker_to_string(invocation);
    }
    if (std::regex_match(invocation, std::regex(mfs_sum_vec.invocation_regex))) {
        return sum_vec_string_invoker_to_string(invocation);
    }
    if (std::regex_match(invocation, std::regex(mfs_vec_to_force.invocation_regex))) {
        return vec_to_force_string_invoker_to_string(invocation);
    }
    if (std::regex_match(invocation, std::regex(mfs_force_to_vec.invocation_regex))) {
        return force_to_vec_string_invoker_to_string(invocation);
    }
    if (std::regex_match(invocation, std::regex(mfs_force_to_string.invocation_regex))) {
        return force_to_string_string_invoker_to_string(invocation);
    }
    if (std::regex_match(invocation, std::regex(mfs_string_to_force.invocation_regex))) {
        return string_to_force_string_invoker_to_string(invocation);
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

std::optional<int> mul_string_invoker(std::string &input) {
std::regex re(R"(^\s*mul\s*\(\s*(-?\d+)\s*,\s*(-?\d+)\s*\)\s*$)");
    std::smatch match;
    if (!std::regex_match(input, match, re)) return std::nullopt;

    auto conversion1 = [](const std::string &s) { return std::stoi(s); };
    int x = conversion1(match[1]);
    auto conversion2 = [](const std::string &s) { return std::stoi(s); };
    int y = conversion2(match[2]);

    int result = mul(x, y);
    return result;
}

std::optional<glm::vec3> mul_vec_string_invoker(std::string &input) {
std::regex re(R"(^\s*mul_vec\s*\(\s*(\s*\(\s*-?\d+(?:\.\d+)?\s*,\s*-?\d+(?:\.\d+)?\s*,\s*-?\d+(?:\.\d+)?\s*\)\s*)\s*,\s*(-?\d+(?:\.\d+)?)\s*\)\s*$)");
    std::smatch match;
    if (!std::regex_match(input, match, re)) return std::nullopt;

    auto conversion1 = [](const std::string &s) { return glm_utils::parse_vec3(s); };
    glm::vec3 v = conversion1(match[1]);
    auto conversion2 = [](const std::string &s) { return std::stof(s); };
    float c = conversion2(match[2]);

    glm::vec3 result = mul_vec(v, c);
    return result;
}

std::optional<float> sum_string_invoker(std::string &input) {
std::regex re(R"(^\s*sum\s*\(\s*(.*)\s*\)\s*$)");
    std::smatch match;
    if (!std::regex_match(input, match, re)) return std::nullopt;

    auto conversion1 = [=](const std::string &input) -> std::vector<float> {
    std::string trimmed = input;
    if (!trimmed.empty() && trimmed.front() == '{' && trimmed.back() == '}') {
        trimmed = trimmed.substr(1, trimmed.size() - 2);
    }

    std::vector<float> result;
    std::regex element_re(R"(-?\d+(?:\.\d+)?)");
    auto begin = std::sregex_iterator(trimmed.begin(), trimmed.end(), element_re);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        try {
            auto conversion = [](const std::string &s) { return std::stof(s); };
            result.push_back(conversion(it->str()));
        } catch (...) {
            // Ignore malformed elements
        }
    }
    return result;
};
    std::vector<float> nums = conversion1(match[1]);

    float result = sum(nums);
    return result;
}

std::optional<glm::vec3> sum_vec_string_invoker(std::string &input) {
std::regex re(R"(^\s*sum_vec\s*\(\s*(.*)\s*\)\s*$)");
    std::smatch match;
    if (!std::regex_match(input, match, re)) return std::nullopt;

    auto conversion1 = [=](const std::string &input) -> std::vector<glm::vec3> {
    std::string trimmed = input;
    if (!trimmed.empty() && trimmed.front() == '{' && trimmed.back() == '}') {
        trimmed = trimmed.substr(1, trimmed.size() - 2);
    }

    std::vector<glm::vec3> result;
    std::regex element_re(R"(\s*\(\s*-?\d+(?:\.\d+)?\s*,\s*-?\d+(?:\.\d+)?\s*,\s*-?\d+(?:\.\d+)?\s*\)\s*)");
    auto begin = std::sregex_iterator(trimmed.begin(), trimmed.end(), element_re);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        try {
            auto conversion = [](const std::string &s) { return glm_utils::parse_vec3(s); };
            result.push_back(conversion(it->str()));
        } catch (...) {
            // Ignore malformed elements
        }
    }
    return result;
};
    std::vector<glm::vec3> vecs = conversion1(match[1]);

    glm::vec3 result = sum_vec(vecs);
    return result;
}

std::optional<Force> vec_to_force_string_invoker(std::string &input) {
std::regex re(R"(^\s*vec_to_force\s*\(\s*(\s*\(\s*-?\d+(?:\.\d+)?\s*,\s*-?\d+(?:\.\d+)?\s*,\s*-?\d+(?:\.\d+)?\s*\)\s*)\s*\)\s*$)");
    std::smatch match;
    if (!std::regex_match(input, match, re)) return std::nullopt;

    auto conversion1 = [](const std::string &s) { return glm_utils::parse_vec3(s); };
    glm::vec3 v = conversion1(match[1]);

    Force result = vec_to_force(v);
    return result;
}

std::optional<glm::vec3> force_to_vec_string_invoker(std::string &input) {
std::regex re(R"(^\s*force_to_vec\s*\(\s*(\s*\(\s*-?\d+(?:\.\d+)?\s*,\s*\s*\(\s*-?\d+(?:\.\d+)?\s*,\s*-?\d+(?:\.\d+)?\s*,\s*-?\d+(?:\.\d+)?\s*\)\s*\s*\)\s*)\s*\)\s*$)");
    std::smatch match;
    if (!std::regex_match(input, match, re)) return std::nullopt;

    auto conversion1 = [](const std::string &s) { return string_to_force(s); };
    Force f = conversion1(match[1]);

    glm::vec3 result = force_to_vec(f);
    return result;
}

std::optional<std::string> force_to_string_string_invoker(std::string &input) {
std::regex re(R"(^\s*force_to_string\s*\(\s*(\s*\(\s*-?\d+(?:\.\d+)?\s*,\s*\s*\(\s*-?\d+(?:\.\d+)?\s*,\s*-?\d+(?:\.\d+)?\s*,\s*-?\d+(?:\.\d+)?\s*\)\s*\s*\)\s*)\s*\)\s*$)");
    std::smatch match;
    if (!std::regex_match(input, match, re)) return std::nullopt;

    auto conversion1 = [](const std::string &s) { return string_to_force(s); };
    Force f = conversion1(match[1]);

    std::string result = force_to_string(f);
    return result;
}

std::optional<Force> string_to_force_string_invoker(std::string &input) {
std::regex re(R"(^\s*string_to_force\s*\(\s*("(?:[^"\\]|\\.)*")\s*\)\s*$)");
    std::smatch match;
    if (!std::regex_match(input, match, re)) return std::nullopt;

    auto conversion1 = [](const std::string &s) { return s; };
    std::string s = conversion1(match[1]);

    Force result = string_to_force(s);
    return result;
}

std::optional<std::string> add_string_invoker_to_string(std::string &input) {
auto opt_result = add_string_invoker(input);
    if (!opt_result) return std::nullopt;
    auto conversion = [](const int &v) { return std::to_string(v); };
    return conversion(*opt_result);
}

std::optional<std::string> mul_string_invoker_to_string(std::string &input) {
auto opt_result = mul_string_invoker(input);
    if (!opt_result) return std::nullopt;
    auto conversion = [](const int &v) { return std::to_string(v); };
    return conversion(*opt_result);
}

std::optional<std::string> mul_vec_string_invoker_to_string(std::string &input) {
auto opt_result = mul_vec_string_invoker(input);
    if (!opt_result) return std::nullopt;
    auto conversion = [](const glm::vec3 &v) { return vec3_to_string(v); };
    return conversion(*opt_result);
}

std::optional<std::string> sum_string_invoker_to_string(std::string &input) {
auto opt_result = sum_string_invoker(input);
    if (!opt_result) return std::nullopt;
    auto conversion = [](const float &v) { return std::to_string(v); };
    return conversion(*opt_result);
}

std::optional<std::string> sum_vec_string_invoker_to_string(std::string &input) {
auto opt_result = sum_vec_string_invoker(input);
    if (!opt_result) return std::nullopt;
    auto conversion = [](const glm::vec3 &v) { return vec3_to_string(v); };
    return conversion(*opt_result);
}

std::optional<std::string> vec_to_force_string_invoker_to_string(std::string &input) {
auto opt_result = vec_to_force_string_invoker(input);
    if (!opt_result) return std::nullopt;
    auto conversion = [](const Force &f) { return force_to_string(f); };
    return conversion(*opt_result);
}

std::optional<std::string> force_to_vec_string_invoker_to_string(std::string &input) {
auto opt_result = force_to_vec_string_invoker(input);
    if (!opt_result) return std::nullopt;
    auto conversion = [](const glm::vec3 &v) { return vec3_to_string(v); };
    return conversion(*opt_result);
}

std::optional<std::string> force_to_string_string_invoker_to_string(std::string &input) {
auto opt_result = force_to_string_string_invoker(input);
    if (!opt_result) return std::nullopt;
    return *opt_result;
}

std::optional<std::string> string_to_force_string_invoker_to_string(std::string &input) {
auto opt_result = string_to_force_string_invoker(input);
    if (!opt_result) return std::nullopt;
    auto conversion = [](const Force &f) { return force_to_string(f); };
    return conversion(*opt_result);
}

