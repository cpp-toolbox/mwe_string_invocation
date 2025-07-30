#include <filesystem>
#include <fstream>
#include <iostream>

#include "utility/logger/logger.hpp"
#include "utility/meta_utils/meta_utils.hpp"

#include "functions/string_invoker/functions.hpp"
#include "utility/regex_utils/regex_utils.hpp"

ConsoleLogger logger;

int main() {
    std::vector<meta_utils::MetaType> extended_concrete_types = meta_utils::concrete_types;
    meta_utils::MetaType glm_vec3_type("glm::vec3", "[](const std::string &s) { return glm_utils::parse_vec3(s); }",
                                       "[](const glm::vec3 &v) { return vec3_to_string(v); }",
                                       regex_utils::float_triplet);
    meta_utils::MetaType glm_vec2_type("glm::vec2", "[](const std::string &s) { return glm_utils::parse_vec2(s); }",
                                       "[](const glm::vec2 &v) { return vec2_to_string(v); }",
                                       regex_utils::float_tuple);
    meta_utils::MetaType force_type("draw_info::IndexedVertexPositions",
                                    "[](const std::string &s) { return string_to_force(s); }",
                                    "[](const Force &f) { return force_to_string(f); }",
                                    regex_utils::tuple_of({regex_utils::float_regex, regex_utils::float_triplet}));

    meta_utils::MetaType meta_type_type("meta_utils::MetaType", "", "", "MetaType");

    extended_concrete_types.push_back(glm_vec3_type);
    extended_concrete_types.push_back(glm_vec2_type);
    extended_concrete_types.push_back(force_type);
    extended_concrete_types.push_back(meta_type_type);

    std::unordered_map<std::string, std::function<meta_utils::MetaType(meta_utils::MetaType)>>
        extended_generic_type_to_meta_type_constructor = meta_utils::generic_type_to_metatype_constructor;

    meta_utils::MetaFunctionSignature ivp_constructor(
        "IndexedVertexPositions(std::vector<unsigned int> indices, std::vector<glm::vec3> xyz_positions, int id = "
        "GlobalUIDGenerator::get_id())",
        meta_utils::create_type_name_to_meta_type_map(extended_concrete_types));

    auto x = meta_utils::generate_string_invoker_for_function(ivp_constructor, extended_concrete_types);

    std::cout << "goob" << std::endl;
    std::cout << x << std::endl;

    meta_utils::generate_string_invokers_from_source_code(
        "src/graphics/vertex_geometry/vertex_geometry.hpp", "src/graphics/vertex_geometry/vertex_geometry.cpp",
        extended_concrete_types, true,
        {" draw_info::IndexedVertexPositions generate_rectangle_between_2d(const "
         "glm::vec2 &p1, const glm::vec2 &p2, float thickness) "},
        meta_utils::FilterMode::Whitelist);

    std::cout << "Enter function invocation strings (type 'quit' to exit):\n";

    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "quit")
            break;

        std::optional<std::string> result = invoke(input, extended_concrete_types);
        if (result.has_value()) {
            std::cout << "Result: " << result.value() << "\n";
        } else {
            std::cout << "Invocation failed.\n";
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}
