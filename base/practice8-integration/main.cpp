#include <cstdlib>
#include <iostream>
#include <format>

#include <functions/polynomial_function.h>

#include <integrators/monte_carlo_integrator.h>
#include <integrators/newton_leibniz_integrator.h>
#include <integrators/riemann_sum_integrator.h>

static void test(
  const Function& function,
  const std::vector<std::unique_ptr<Integrator>>& integrators,
  const std::vector<std::pair<float, float>> intervals)
{
  {
    std::cout << "Testing the following integrators: ";
    bool is_first = true;
    for (const auto& integrator : integrators) {
      if (is_first) {
        is_first = !is_first;
      }
      else {
        std::cout << " / ";
      }
      std::cout << *integrator;
    }
    std::cout << ".\n";
  }

  for (const auto& [a, b] : intervals) {
    std::cout << std::format("[{:>5}; {:>5}] ", a, b);
    for (const auto& integrator : integrators) {
      std::cout << std::format("{:>8.3f}", integrator->compute(function, a, b));
    }
    std::cout << '\n';
  }
}

int main() {
  constexpr float dx = 0.001f;
  constexpr double point_density = 1'000;

  // 2x^3 + 6x^2 - 4x + 1
  // https://www.wolframalpha.com/input?i=plot+2x%5E3%2B6x%5E2-4x%2B1+from+x%3D-4+to+%2B2
  PolynomialFunction polynom({ 2, 6, -4, 1 });

  std::cout << "f(x) = " << polynom << '\n';
  std::cout << "F(x) = " << *polynom.antidifferentiate() << "\n\n";

  std::vector<std::unique_ptr<Integrator>> integrators;
  integrators.push_back(std::make_unique<NewtonLeibnizIntegrator>());
  integrators.push_back(std::make_unique<RiemannSumIntegrator>(dx));
  integrators.push_back(std::make_unique<MonteCarloIntegrator>(dx, point_density));

  test(
    polynom,
    integrators,
    {
      {-4.0f, 0.0f},
      {-4.0f, -3.75f},
      {-4.0f, -3.0f},
      {-3.0f, -2.0f},
      {1.0f, 2.0f}
    }
  );

  return EXIT_SUCCESS;
}
