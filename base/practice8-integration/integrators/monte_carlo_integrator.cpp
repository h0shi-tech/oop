#include <integrators/monte_carlo_integrator.h>

MonteCarloIntegrator::MonteCarloIntegrator(const float dx, const double point_density) :
  _dx(dx), _point_density(point_density) { }

std::string MonteCarloIntegrator::name() const {
  return "Monte Carlo";
}

float MonteCarloIntegrator::compute(const Function& function, const float a, const float b) const {
  // TODO MonteCarloIntegrator::compute
  // Доступные параметры: _dx, _point_density, _e
  return 0.0f;
}
