#include "Polynomial.h"

#include <iostream>
#include <sstream>
Polynomial::Polynomial(const DoubleArray &coefficients) : _coefficients{coefficients} {
    size_t last_zero_index = coefficients.size();
    for (size_t i = coefficients.size() - 1; i >= 0; --i) {
        if (coefficients[i] != 0) {
            break;
        } else {
            last_zero_index = i;
        }
    }

    _coefficients.erase(_coefficients.begin() + last_zero_index, _coefficients.end());
}

Polynomial::Polynomial(const Polynomial &other) : _coefficients{ other._coefficients } {}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    _coefficients = other._coefficients;
    return *this;
}

std::string Polynomial::to_string() const {
    std::stringstream string;

    string << "(\t";

    for (double _coefficient : _coefficients) {
        string.precision(2);
        string << _coefficient << "\t";
    }
    string << ')';

    return string.str();
}

bool Polynomial::operator==(const Polynomial& other) const {
    if (_coefficients.size() != other._coefficients.size())
        return false;

    for (size_t i = 0; i < _coefficients.size(); ++i) {
        if (_coefficients[i] != other._coefficients[i])
            return false;
    }
    return true;
}
bool Polynomial::operator!=(const Polynomial& other) const {
    return !operator==(other);
}

Polynomial Polynomial::operator-() const {
    Polynomial result = *this;

    for (size_t i = 0; i < _coefficients.size(); ++i)
        result._coefficients[i] = -_coefficients[i];

    return result;
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    size_t const size = std::min(_coefficients.size(), other._coefficients.size());

    Polynomial result = *this;
    for (size_t i = 0; i < size; ++i) {
        result._coefficients[i] += other._coefficients[i];
    }
    return result;
}
Polynomial Polynomial::operator-(const Polynomial& other) const {

    size_t const size = std::min(_coefficients.size(), other._coefficients.size());

    Polynomial result = *this;
    for (size_t i = 0; i < size; ++i) {
        result._coefficients[i] -= other._coefficients[i];
    }
    return result;
}
Polynomial Polynomial::operator*(const Polynomial& other) const {

    size_t const size = std::min(_coefficients.size(), other._coefficients.size());

    Polynomial result = *this;
    for (size_t i = 0; i < size; ++i) {
        result._coefficients[i] *= other._coefficients[i];
    }
    return result;
}
Polynomial Polynomial::operator/(double number) const {
    if (number == 0)
        return *this;

    Polynomial result = *this;
    for (size_t i = 0; i < size(); ++i) {
        result._coefficients[i] /= number;
    }
    return result;
}
Polynomial& Polynomial::operator+=(const Polynomial& other) {
    size_t const size = std::min(_coefficients.size(), other._coefficients.size());

    for (size_t i = 0; i < size; ++i) {
        if (other._coefficients[i] != 0)
            _coefficients[i] += other._coefficients[i];
    }
    return *this;
}
Polynomial& Polynomial::operator-=(const Polynomial& other) {

    size_t const size = std::min(_coefficients.size(), other._coefficients.size());

    for (size_t i = 0; i < size; ++i) {
        if (other._coefficients[i] != 0)
            _coefficients[i] -= other._coefficients[i];
    }
    return *this;
}
Polynomial& Polynomial::operator*=(const Polynomial& other) {

    size_t const size = std::min(_coefficients.size(), other._coefficients.size());

    for (size_t i = 0; i < size; ++i) {
        if (other._coefficients[i] != 0)
            _coefficients[i] *= other._coefficients[i];
    }
    return *this;
}
Polynomial& Polynomial::operator/=(double number) {
    if (number == 0)
        return *this;

    for (size_t i = 0; i < size(); ++i) {
        _coefficients[i] /= number;
    }
    return *this;
}
double Polynomial::operator[](size_t index) const {
    if (index >= 0 && index < _coefficients.size())
        return _coefficients[index];

    throw std::out_of_range{ "Invalid index" };
}

size_t Polynomial::size() const {
    return _coefficients.size();
}

Polynomial Polynomial::operator<<(uint8_t shift) const {
    if (shift >= _coefficients.size())
        return *this;

    Polynomial result = *this;

    for (size_t i = 0; i < _coefficients.size() - shift; ++i) {
        result._coefficients[i] = _coefficients[i + shift];
    }
    for (size_t i = _coefficients.size() - shift; i < _coefficients.size(); ++i) {
        result._coefficients[i] = _coefficients[i - (_coefficients.size() - shift)];
    }
    return result;
}
Polynomial Polynomial::operator>>(uint8_t shift) const {
    if (shift >= _coefficients.size())
        return *this;

    Polynomial result = *this;

    for (size_t i = 0; i < shift; ++i) {
        result._coefficients[i] = _coefficients[i + (_coefficients.size() - shift)];
    }
    for (size_t i = shift; i < _coefficients.size(); ++i) {
        result._coefficients[i] = _coefficients[i - shift];
    }
    return result;
}
