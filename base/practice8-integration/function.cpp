#include <function.h>

std::ostream& operator<<(std::ostream& stream, const Function& function) {
  return stream << function.to_string();
}
