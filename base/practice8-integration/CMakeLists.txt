cmake_minimum_required(VERSION 3.5)

project("practice8-integration" CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
  "functions/polynomial_function.cpp"
  "functions/polynomial_function.h"
  "integrators/monte_carlo_integrator.cpp"
  "integrators/monte_carlo_integrator.h"
  "integrators/newton_leibniz_integrator.cpp"
  "integrators/newton_leibniz_integrator.h"
  "integrators/riemann_sum_integrator.cpp"
  "integrators/riemann_sum_integrator.h"
  "function.cpp"
  "function.h"
  "integrator.cpp"
  "integrator.h"
  "main.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
