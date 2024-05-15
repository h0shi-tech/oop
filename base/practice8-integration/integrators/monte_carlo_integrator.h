#pragma once

#include <random>

#include <integrator.h>

class MonteCarloIntegrator final : public Integrator {
private:
  float _dx;
  double _point_density;
  std::default_random_engine _e;

public:
  MonteCarloIntegrator(float dx, double point_density);

  std::string name() const override;

  float compute(const Function & function, float a, float b) const override;
};
