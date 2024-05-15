#include <integrator.h>

std::ostream& operator<<(std::ostream& stream, const Integrator& integrator) {
  return stream << integrator.name();
}
