#pragma once

#include <vector>
#include <string>

using DoubleArray = std::vector<double>;

class Polynomial {
    DoubleArray _coefficients;

public:
    explicit Polynomial(const DoubleArray &coefficients);
    Polynomial(const Polynomial& other);

    Polynomial& operator=(const Polynomial& other);

    [[nodiscard]] std::string to_string() const;

    bool operator==(const Polynomial& other) const;
    bool operator!=(const Polynomial& other) const;

    Polynomial operator-() const;

    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator-(const Polynomial& other) const;
    Polynomial operator*(const Polynomial& other) const;
    Polynomial operator/(double number) const;

    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);
    Polynomial& operator/=(double number);

    Polynomial operator<<(uint8_t shift) const;
    Polynomial operator>>(uint8_t shift) const;

    double operator[](size_t index) const;

    [[nodiscard]] size_t size() const;
};