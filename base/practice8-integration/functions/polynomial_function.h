#pragma once

#include <vector>

#include <function.h>

class PolynomialFunction final : public Function {
private:
  std::vector<float> _coeffs;

public:
  PolynomialFunction(std::vector<float> coeffs);

  float compute(float x) const override;

  std::unique_ptr<Function> antidifferentiate() const override;

  std::string to_string() const override;
};
