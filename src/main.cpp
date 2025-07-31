#include <filesystem>
#include <fstream>
#include <iostream>

#include "utility/logger/logger.hpp"
#include "utility/meta_utils/meta_utils.hpp"

#include "graphics/vertex_geometry/string_invoker/vertex_geometry.hpp"
#include "utility/regex_utils/regex_utils.hpp"

// NOTE was working on
// meta_utils::generate_string_invokers_from_source_code(
// but the function parsing is totoally wrong..., need to fix that. next

ConsoleLogger logger;

int main() {
    std::vector<meta_utils::MetaType> extended_concrete_types = meta_utils::concrete_types;
    meta_utils::MetaType glm_vec3_type("glm::vec3", "[](const std::string &s) { return glm_utils::parse_vec3(s); }",
                                       "[](const glm::vec3 &v) { return vec3_to_string(v); }",
                                       regex_utils::float_triplet);
    meta_utils::MetaType glm_vec2_type("glm::vec2", "[](const std::string &s) { return glm_utils::parse_vec2(s); }",
                                       "[](const glm::vec2 &v) { return vec2_to_string(v); }",
                                       regex_utils::float_tuple);

    meta_utils::MetaType meta_type_type("meta_utils::MetaType", "", "", "MetaType");

    extended_concrete_types.push_back(glm_vec3_type);
    extended_concrete_types.push_back(glm_vec2_type);
    extended_concrete_types.push_back(meta_type_type);

    std::unordered_map<std::string, std::function<meta_utils::MetaType(meta_utils::MetaType)>>
        extended_generic_type_to_meta_type_constructor = meta_utils::generic_type_to_metatype_constructor;

    meta_utils::MetaFunctionSignature ivp_constructor(
        "IndexedVertexPositions(std::vector<unsigned int> indices, std::vector<glm::vec3> xyz_positions, int id = "
        "GlobalUIDGenerator::get_id())",
        "", meta_utils::create_type_name_to_meta_type_map(extended_concrete_types));

    auto x = meta_utils::generate_string_invoker_for_function(ivp_constructor, extended_concrete_types);

    meta_utils::MetaFunction mfx(x, meta_utils::create_type_name_to_meta_type_map(extended_concrete_types));

    meta_utils::MetaType ivp_type(
        "draw_info::IndexedVertexPositions", mfx.to_lambda_string(),
        "[](const draw_info::IndexedVertexPositions &ivp) { std::ostringstream oss; oss << ivp; return oss.str(); } ",
        regex_utils::tuple_of({regex_utils::float_regex, regex_utils::float_triplet}));

    extended_concrete_types.push_back(ivp_type);

    meta_utils::generate_string_invokers_from_source_code(
        "src/graphics/vertex_geometry/vertex_geometry.hpp", "src/graphics/vertex_geometry/vertex_geometry.cpp",
        extended_concrete_types, true,
        {" draw_info::IndexedVertexPositions generate_rectangle_between_2d(const "
         "glm::vec2 &p1, const glm::vec2 &p2, float thickness) "},
        meta_utils::FilterMode::Whitelist);

    start_interactive_invoker(extended_concrete_types);

    return 0;
}
