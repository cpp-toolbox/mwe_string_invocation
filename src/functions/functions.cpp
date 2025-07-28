#include "functions.hpp"
#include "../utility/regex_utils/regex_utils.hpp"
#include <iostream>
#include <sstream>

int add(int x, int y) { return x + y; }
int mul(int x, int y) { return x * y; }
glm::vec3 mul_vec(glm::vec3 v, float c) { return v * c; }

float sum(std::vector<float> nums) {
    float sum = 0;
    for (const auto &n : nums) {
        sum += n;
    }
    return sum;
}

glm::vec3 sum_vec(std::vector<glm::vec3> vecs) {
    glm::vec3 sum(0.0f);
    for (const auto &v : vecs) {
        sum += v;
    }
    return sum;
}

Force vec_to_force(glm::vec3 v) {
    float mag = glm::length(v);
    glm::vec3 dir = mag > 0.0f ? glm::normalize(v) : glm::vec3(0.0f);
    return Force(mag, dir);
}

glm::vec3 force_to_vec(Force f) { return f.magnitude * f.direction; }

std::string force_to_string(Force f) {
    std::ostringstream oss;
    oss << f.magnitude << "," << f.direction.x << "," << f.direction.y << "," << f.direction.z;
    return oss.str();
}

Force string_to_force(std::string s) {

    const std::string force_pattern_str =
        regex_utils::tuple_of({regex_utils::captured_float_regex, regex_utils::captured_float_triplet});

    const std::regex force_regex(force_pattern_str);
    std::smatch match;

    if (!std::regex_match(s, match, force_regex)) {
        throw std::invalid_argument("Invalid Force string format");
    }

    float magnitude = std::stof(match[1].str());
    float x = std::stof(match[2].str());
    float y = std::stof(match[3].str());
    float z = std::stof(match[4].str());

    return Force(magnitude, glm::vec3(x, y, z));
}
