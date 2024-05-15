#pragma once

#include <format>
#include <stdexcept>

class NonCopyable {
public:
  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;

protected:
  NonCopyable() = default;
  ~NonCopyable() = default;
};

template<typename T>
void validate_range(const T value, const T min_value, const T max_value, const char* const variable_name) {
  if (value < min_value || max_value < value) {
    throw std::runtime_error(std::format(
      "The value {} of the variable `{}` is not in range [{}; {}].",
      value,
      variable_name,
      min_value,
      max_value
    ));
  }
}

#define VALIDATE_RANGE(value, min_value, max_value) validate_range(value, min_value, max_value, #value)
