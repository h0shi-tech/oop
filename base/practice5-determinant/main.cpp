#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace std;

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

ostream& operator<<(ostream& stream, const IMatrix& matrix) {
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
  vector<float> _data;
  size_t _rows;
  size_t _cols;

public:
  Matrix(const size_t rows, const size_t cols) : _data(rows* cols, 0), _rows(rows), _cols(cols) { }

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

// ====
// main
// ====

int main() {
  Matrix m(3, 6);

  cout << m;

  return 0;
}
