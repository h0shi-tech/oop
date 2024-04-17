#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

// =======
// IMatrix
// =======

class IMatrix {
public:
  virtual size_t rows() const noexcept = 0;
  virtual size_t cols() const noexcept = 0;
  virtual float get(size_t i, size_t j) const = 0;
  virtual void set(size_t i, size_t j, float value) = 0;

  IMatrix(const IMatrix&) = delete;
  IMatrix& operator=(const IMatrix&) = delete;
  virtual ~IMatrix() = default;

protected:
  IMatrix() = default;
};

std::ostream& operator<<(std::ostream& stream, const IMatrix& matrix) {
  for (size_t i = 0; i < matrix.rows(); ++i) {
    for (size_t j = 0; j < matrix.cols(); ++j) {
      stream << matrix.get(i, j) << '\t';
    }
    stream << '\n';
  }
  return stream;
}

// ======
// Matrix
// ======

class Matrix : public IMatrix {
private:
  std::vector<float> _data;
  size_t _rows;
  size_t _cols;

public:
  Matrix(const size_t rows, const size_t cols) :
    _data(rows * cols, 0),
    _rows(rows),
    _cols(cols)
  { }

  size_t rows() const noexcept override {
    return _rows;
  }

  size_t cols() const noexcept override {
    return _cols;
  }

  float get(size_t i, size_t j) const override {
    return _data[i * _cols + j];
  }

  void set(size_t i, size_t j, float value) override {
    _data[i * _cols + j] = value;
  }
};

// ==============
// ConstSubMatrix
// ==============

class ConstSubMatrix : public IMatrix {
private:
  const IMatrix& _m;
  size_t _di;
  size_t _dj;

public:
  ConstSubMatrix(const IMatrix& m, size_t di, size_t dj) :
    _m(m),
    _di(di),
    _dj(dj)
  { }

  size_t rows() const noexcept override {
    return _m.rows() - 1;
  }

  size_t cols() const noexcept override {
    return _m.cols() - 1;
  }

  float get(size_t i, size_t j) const override {
    if (i >= _di) { i++; }
    if (j >= _dj) { j++; }
    return _m.get(i, j);
  }

  void set(size_t i, size_t j, float value) override {
    throw std::logic_error("ConstSubMatrix is const.");
  }
};

// ===
// det
// ===

double det(const IMatrix& m) {
  const auto n = m.rows();

  if (n != m.cols()) {
    throw std::logic_error("Matrix is not square.");
  }

  if (n == 1) {
    return m.get(0, 0);
  }

  double res = 0;

  for (size_t j = 0; j < n; ++j) {
    const ConstSubMatrix sm(m, 0, j);
    res += (j % 2 == 0 ? +1 : -1) * m.get(0, j) * det(sm);
  }

  return res;
}


// ====
// main
// ====

int main() {
  Matrix m(4, 4);
  m.set(0, 0, 1);
  m.set(0, 1, 7);
  m.set(0, 2, 4);
  m.set(0, 3, 5);
  m.set(1, 0, 8);
  m.set(1, 1, 3);
  m.set(1, 2, 8);
  m.set(1, 3, 7);
  m.set(2, 0, 3);
  m.set(2, 1, 4);
  m.set(2, 2, 7);
  m.set(2, 3, 1);
  m.set(3, 0, 1);
  m.set(3, 1, 4);
  m.set(3, 2, 1);
  m.set(3, 3, 0);

  std::cout << m << std::endl;

  std::cout << std::fixed << det(m) << std::endl;

  // Wolfram Alpha:
  // https://www.wolframalpha.com/input?i=det+%7B%7B1%2C+7%2C+4%2C+5%7D%2C+%7B8%2C+3%2C+8%2C+7%7D%2C+%7B3%2C+4%2C+7%2C+1%7D%2C+%7B1%2C+4%2C+1%2C+0%7D%7D

  return 0;
}
