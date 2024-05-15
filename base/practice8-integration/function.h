#pragma once

#include <memory>
#include <ostream>
#include <string>

class Function {
public:
  virtual float compute(float x) const = 0;
  virtual std::unique_ptr<Function> antidifferentiate() const = 0;
  virtual std::string to_string() const = 0;

  Function(const Function&) = delete;
  Function operator=(const Function&) = delete;

  virtual ~Function() = default;

protected:
  Function() = default;
};

std::ostream& operator<<(std::ostream& stream, const Function& function);
