#pragma once
#include <vector>

class Vector {
public:

    Vector() = default;

    Vector(const std::vector<double>& vec);

    Vector(size_t size);

    void Init(size_t size);

    void RandomFill();

    size_t Size() const;

    double& operator[](size_t ind);

    double operator[](size_t ind) const;

    void operator += (const Vector& other);

    Vector operator + (const Vector& other) const;

    void operator -= (const Vector& other);

    Vector operator - (const Vector& other) const;

    void operator *= (double value);

    Vector operator * (double value) const;

    double operator * (const Vector& other) const;

    std::pair<int, double> FindMax();

    friend std::ostream& operator << (std::ostream& os, const Vector& vec);
    friend std::istream& operator >> (std::istream& is, Vector& vec);

private:
    size_t size_ = 0;
    std::vector<double> vec_;
};
 
class Matrix {
public:
    Matrix() = default;

    Matrix(const std::vector<std::vector<double>>& mat);

    Matrix(size_t rows, size_t cols);

    void Init(size_t rows, size_t cols);

    void RandomFill();

    size_t GetRows() const;

    size_t GetCols() const;

    Vector& operator[](size_t ind);

    const Vector& operator[](size_t ind) const;

    void operator += (const Matrix& other);

    Matrix operator + (const Matrix& other) const;

    void operator -= (const Matrix& other);

    Matrix operator - (const Matrix& other) const;

    void operator *= (double value);

    Matrix operator * (double value) const;

    Vector operator * (const Vector& other) const;

    Matrix T() const;

    friend std::ostream& operator << (std::ostream& os, const Matrix& vec);
    friend std::istream& operator >> (std::istream& is, Matrix& vec);
private:
    std::vector<Vector> matrix_;
    size_t rows_ = 0, cols_ = 0;
};