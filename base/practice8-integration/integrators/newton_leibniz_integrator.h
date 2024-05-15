#pragma once

#include <integrator.h>

class NewtonLeibnizIntegrator final : public Integrator {
public:
  std::string name() const override;

  float compute(const Function & function, float a, float b) const override;
};
