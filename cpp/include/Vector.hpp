// Vector3D class resembling a spatial 3-dimensional vector

#pragma once

#include <array>
#include <cmath>
#include <ostream>

class Vector3D
{
private:
  double x;
  double y;
  double z;

public:
  // Constructors
  Vector3D() : x{0}, y{0}, z{0} {}
  Vector3D(double x_, double y_, double z_) : x{x_}, y{y_}, z{z_} {}
  Vector3D(double value) : x{value}, y{value}, z{value} {}

  // Constant vectors
  static const Vector3D ZERO;
  static const Vector3D UNITX;
  static const Vector3D UNITY;
  static const Vector3D UNITZ;

  // Getters
  double getX() const { return x; }
  double getY() const { return y; }
  double getZ() const { return z; }

  // Setters
  void setX(double x_) { x = x_; }
  void setY(double y_) { y = y_; }
  void setZ(double z_) { z = z_; }

  // Operators
  Vector3D operator+(const Vector3D &other) const;
  Vector3D operator-(const Vector3D &other) const;
  Vector3D &operator+=(const Vector3D &other);
  Vector3D &operator-=(const Vector3D &other);
  Vector3D operator*(double scalar) const;
  Vector3D operator/(double scalar) const;
  Vector3D &operator*=(double scalar);
  Vector3D &operator/=(double scalar);

  // LHS scalar
  friend Vector3D operator*(double scalar, const Vector3D &v);

  // Comparison
  bool operator==(const Vector3D &other) const;
  bool operator!=(const Vector3D &other) const;

  // Maths
  double dot(const Vector3D &other) const;
  Vector3D cross(const Vector3D &other) const;
  double magnitude() const;
  double squaredMagnitude() const;
  Vector3D normalise() const;
  double distance(const Vector3D &other) const;
  double angle(const Vector3D &other) const;
  Vector3D projectOnto(const Vector3D &other) const;

  // Validation
  bool isZero() const;

  // ostream
  friend std::ostream &operator<<(std::ostream &os, const Vector3D &v);
};