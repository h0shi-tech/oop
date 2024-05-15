#include <integrators/riemann_sum_integrator.h>

RiemannSumIntegrator::RiemannSumIntegrator(const float dx) : _dx(dx) { }

std::string RiemannSumIntegrator::name() const {
  return "Riemann Sum";
}

float RiemannSumIntegrator::compute(const Function& function, const float a, const float b) const {
  // TODO RiemannSumIntegrator::compute
  // Доступные параметры: _dx
  return 0.0f;
}
