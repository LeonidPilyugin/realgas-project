// 
// vector.hpp
// 
// Contains Vector struct and some operator overloads
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#pragma once

// struct Vector
// 
// Describes a 3D vector
// 
// Fields:
// 1) float x -- x coordinate
// 2) float y -- y coordinate
// 3) float z -- z coordinate
// 
// Methods:
// 1) Vector()
// 2) Vector(const Vector& v)
// 
// Operator overloads:
// 1) Vector& operator+=(const Vector &right)
// 2) Vector& operator-=(const Vector &right)
// 3) Vector& operator*=(float right)
// 4) Vector& operator/=(float right)
// 5) Vector operator+(const Vector &left, const Vector &right)
// 6) Vector operator-(const Vector &left, const Vector &right)
// 7) Vector operator*(const Vector &left, float right)
// 8) Vector operator/(const Vector &left, float right)
// 9) float operator*(const Vector &left, const Vector &right)
// 
struct Vector {
    float x, y, z;  // coordinates

    // Vector()
    // 
    // Default constructor
    // 
    // Arguments: no
    // 
    // Notes:
    // 1) Creates a (0.0f, 0.0f, 0.0f) vector
    // 
    Vector();

    // Vector(const Vector& v)
    // 
    // Copy constructor
    // 
    // Arguments:
    // 1) const Vector& v -- Vector to copy
    // 
    Vector(const Vector& v);

    // Vector& operator+=(const Vector &right)
    // 
    // Coordinate += operator
    // 
    // Arguments:
    // 1) const Vector &right -- right operand
    // 
    // Returns *this
    // 
    Vector& operator+=(const Vector &right);

    // Vector& operator-=(const Vector &right)
    // 
    // Coordinate -= operator
    // 
    // Arguments:
    // 1) const Vector &right -- right operand
    // 
    // Returns *this
    // 
    Vector& operator-=(const Vector &right);

    // Vector& operator*=(float right)
    // 
    // Coordinate *= operator
    // 
    // Arguments:
    // 1) float right -- right operand
    // 
    // Returns *this
    // 
    Vector& operator*=(float right);

    // Vector& operator/=(float right)
    // 
    // Coordinate /= operator
    // 
    // Arguments:
    // 1) float right -- right operand
    // 
    // Returns *this
    // 
    Vector& operator/=(float right);
};

// Vector operator+(const Vector &left, const Vector &right)
// 
// Coordinate + operator
// 
// Arguments:
// 1) const Vector &left -- left operand
// 2) const Vector &right -- right operand
// 
// Returns left + right
// 
Vector operator+(const Vector &left, const Vector &right);

// Vector operator-(const Vector &left, const Vector &right)
// 
// Coordinate - operator
// 
// Arguments:
// 1) const Vector &left -- left operand
// 2) const Vector &right -- right operand
// 
// Returns left - right
// 
Vector operator-(const Vector &left, const Vector &right);

// Vector operator*(const Vector &left, float right)
// 
// Coordinate * operator
// 
// Arguments:
// 1) const Vector &left -- left operand
// 2) float right -- right operand
// 
// Returns left * right
// 
Vector operator*(const Vector &left, float right);

// Vector operator/(const Vector &left, float right)
// 
// Coordinate / operator
// 
// Arguments:
// 1) const Vector &left -- left operand
// 2) float right -- right operand
// 
// Returns left / right
// 
Vector operator/(const Vector &left, float right);

// float operator*(const Vector &left, const Vector &right)
// 
// Scalar multiplication
// 
// Arguments:
// 1) const Vector &left -- left operand
// 2) const Vector &right -- right operand
// 
// Returns (left, right)
// 
float operator*(const Vector &left, const Vector &right);
