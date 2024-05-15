#include <integrators/newton_leibniz_integrator.h>

std::string NewtonLeibnizIntegrator::name() const {
  return "Newton-Leibniz";
}

float NewtonLeibnizIntegrator::compute(const Function& function, const float a, const float b) const {
  const auto antiderivative = function.antidifferentiate();

  return antiderivative->compute(b) - antiderivative->compute(a);
}
