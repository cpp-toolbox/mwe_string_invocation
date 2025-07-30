cmake_minimum_required(VERSION 3.10)
project(mwe_string_invocation)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB_RECURSE SOURCES "src/*.cpp")
# Add the main executable
add_executable(${PROJECT_NAME} ${SOURCES})
        

# Automatically generated from conan install

# Automatically generated from conan install

# Automatically generated from conan install
find_package(glm)
find_package(fmt)
target_link_libraries(${PROJECT_NAME} glm::glm fmt::fmt)
