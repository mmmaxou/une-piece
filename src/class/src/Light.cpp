#include <glimac/glm.hpp>

#include <class/Light.hpp>

namespace UP
{

Light::Light()
    : _direction(glm::vec4(1.f, 1.f, 1.f, 0.f)),
      _intensity(glm::vec4(3.f)){};

} // namespace UP