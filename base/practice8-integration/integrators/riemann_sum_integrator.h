#pragma once

#include <integrator.h>

class RiemannSumIntegrator final : public Integrator {
private:
  float _dx;

public:
  RiemannSumIntegrator(float dx);

  std::string name() const override;

  float compute(const Function & function, float a, float b) const override;
};
