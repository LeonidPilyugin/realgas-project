// 
// vector.cpp
// 
// This file contains Vector functions definitions
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 

#include "vector.hpp"

Vector::Vector() {
    x = y = z = 0.0f;
}

Vector::Vector(const Vector &v) {
    *this = v;
}

Vector& Vector::operator+=(const Vector &right) {
    return *this = *this + right;
}

Vector& Vector::operator-=(const Vector &right) {
    return *this = *this - right;
}

Vector& Vector::operator*=(float right) {
    return *this = *this * right;
}

Vector& Vector::operator/=(float right) {
    return *this = *this / right;
}

Vector operator+(const Vector &left, const Vector &right) {
    Vector result;
    result.x = left.x + right.x;
    result.y = left.y + right.y;
    result.z = left.z + right.z;
    return result;
}

Vector operator-(const Vector &left, const Vector &right) {
    Vector result;
    result.x = left.x - right.x;
    result.y = left.y - right.y;
    result.z = left.z - right.z;
    return result;
}

Vector operator*(const Vector &left, float right) {
    Vector result;
    result.x = left.x * right;
    result.y = left.y * right;
    result.z = left.z * right;
    return result;
}

Vector operator/(const Vector &left, float right) {
    return left * (1.0f / right);
}

float operator*(const Vector &left, const Vector &right) {
    return left.x * right.x + left.y * right.y + left.z * right.z;
}
