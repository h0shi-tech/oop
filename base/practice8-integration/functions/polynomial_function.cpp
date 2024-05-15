#include <functions/polynomial_function.h>

#include <cmath>
#include <iomanip>
#include <sstream>

PolynomialFunction::PolynomialFunction(std::vector<float> coeffs) : _coeffs(std::move(coeffs)) { }

float PolynomialFunction::compute(float x) const {
  if (_coeffs.empty()) {
    return 0;
  }

  const auto n = _coeffs.size();
  float value = _coeffs.back();
  float xp = x;

  for (size_t i = 1; i < n; ++i) {
    value += _coeffs[n - 1 - i] * xp;
    xp *= x;
  }

  return value;
}

std::unique_ptr<Function> PolynomialFunction::antidifferentiate() const {
  std::vector<float> coeffs;

  coeffs.reserve(_coeffs.size() + 1);
  coeffs.assign(_coeffs.begin(), _coeffs.end());
  coeffs.push_back(0);

  const auto n = coeffs.size();

  for (size_t i = 2; i < n; ++i) {
    coeffs[i - 2] /= (n - i + 1);
  }

  return std::make_unique<PolynomialFunction>(coeffs);
}

std::string PolynomialFunction::to_string() const {
  if (_coeffs.empty()) {
    return "0";
  }

  const auto n = _coeffs.size();
  std::stringstream ss;

  for (size_t i = 0; i < n; ++i) {
    const auto c = _coeffs[i];

    if (c == 0) {
      continue;
    }

    ss << std::showpos << c;

    const auto p = n - 1 - i;
    if (p > 1) {
      ss << "*x^" << (n - 1 - i);
    }
    else if (p == 1) {
      ss << "*x";
    }
  }

  return ss.str();
}
