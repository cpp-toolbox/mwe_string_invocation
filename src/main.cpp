#include <iostream>
#include <fstream>
#include <filesystem>

#include "utility/meta_utils/meta_utils.hpp"
#include "utility/logger/logger.hpp"

#include "functions/string_invoker/functions.hpp"
#include "utility/regex_utils/regex_utils.hpp"

ConsoleLogger logger;

// NOTE: aboutodo
// * was adding a whitelist feature that goes all the way down to mfc
// * then we can do that only on the functions we want to do from vertex_geom
// * then we can integrate that into the other project.

int main() {
    std::vector<meta_utils::MetaType> extended_concrete_types = meta_utils::concrete_types;
    meta_utils::MetaType glm_vec3_type("glm::vec3", "[](const std::string &s) { return glm_utils::parse_vec3(s); }",
                                       "[](const glm::vec3 &v) { return vec3_to_string(v); }",
                                       regex_utils::float_triplet);
    meta_utils::MetaType glm_vec2_type("glm::vec2", "[](const std::string &s) { return glm_utils::parse_vec2(s); }",
                                       "[](const glm::vec2 &v) { return vec2_to_string(v); }",
                                       regex_utils::float_tuple);
    meta_utils::MetaType force_type("Force", "[](const std::string &s) { return string_to_force(s); }",
                                    "[](const Force &f) { return force_to_string(f); }",
                                    regex_utils::tuple_of({regex_utils::float_regex, regex_utils::float_triplet}));
    meta_utils::MetaType meta_type_type("meta_utils::MetaType", "", "", "MetaType");

    extended_concrete_types.push_back(glm_vec3_type);
    extended_concrete_types.push_back(glm_vec2_type);
    extended_concrete_types.push_back(force_type);
    extended_concrete_types.push_back(meta_type_type);

    std::unordered_map<std::string, std::function<meta_utils::MetaType(meta_utils::MetaType)>>
        extended_generic_type_to_meta_type_constructor = meta_utils::generic_type_to_metatype_constructor;

    meta_utils::generate_string_invokers_from_source_code("src/functions/functions.hpp", "src/functions/functions.cpp",
                                                          extended_concrete_types, true, {"int add(int x, int y)"},
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
