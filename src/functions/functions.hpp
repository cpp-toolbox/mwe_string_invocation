#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <glm/glm.hpp>
#include <string>
#include <vector>

class Force {
  public:
    float magnitude;
    glm::vec3 direction;

    Force(float magnitude, glm::vec3 direction) : magnitude(magnitude), direction(direction) {}
};

std::string force_to_string(Force f);
Force string_to_force(std::string s);

int add(int x, int y);
int mul(int x, int y);
glm::vec3 mul_vec(glm::vec3 v, float c);
float sum(std::vector<float> nums);
glm::vec3 sum_vec(std::vector<glm::vec3> vecs);
Force vec_to_force(glm::vec3 v);
glm::vec3 force_to_vec(Force f);

#endif // FUNCTIONS_HPP
