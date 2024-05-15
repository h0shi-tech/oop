#pragma once

#include <ostream>
#include <string>

#include <function.h>

class Integrator {
public:
  virtual std::string name() const = 0;
  virtual float compute(const Function& function, float a, float b) const = 0;

  Integrator(const Integrator&) = delete;
  Integrator operator=(const Integrator&) = delete;

  virtual ~Integrator() = default;

protected:
  Integrator() = default;
};

std::ostream& operator<<(std::ostream& stream, const Integrator& integrator);
