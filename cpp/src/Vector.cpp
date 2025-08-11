// Implementation of Vector3D class

#include "Vector.hpp"

// Constant vectors
const Vector3D Vector3D::ZERO{0, 0, 0};
const Vector3D Vector3D::UNITX{1, 0, 0};
const Vector3D Vector3D::UNITY{0, 1, 0};
const Vector3D Vector3D::UNITZ{0, 0, 1};

// Operators
Vector3D Vector3D::operator+(const Vector3D &other) const
{
  return {x + other.x, y + other.y, z + other.z};
}

Vector3D Vector3D::operator-(const Vector3D &other) const
{
  return {x - other.x, y - other.y, z - other.z};
}

Vector3D &Vector3D::operator+=(const Vector3D &other)
{
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

Vector3D &Vector3D::operator-=(const Vector3D &other)
{
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

Vector3D Vector3D::operator*(double scalar) const
{
  return {x * scalar, y * scalar, z * scalar};
}

Vector3D Vector3D::operator/(double scalar) const
{
  return {x / scalar, y / scalar, z / scalar};
}

Vector3D &Vector3D::operator*=(double scalar)
{
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

Vector3D &Vector3D::operator/=(double scalar)
{
  x /= scalar;
  y /= scalar;
  z /= scalar;
  return *this;
}

// LHS scalar (friend)
Vector3D operator*(double scalar, const Vector3D &v)
{
  return {v.x * scalar, v.y * scalar, v.z * scalar};
}

// Comparison
bool Vector3D::operator==(const Vector3D &other) const
{
  return x == other.x && y == other.y && z == other.z;
}

bool Vector3D::operator!=(const Vector3D &other) const
{
  return !(*this == other); // Uses operator ==
}

// Maths
double Vector3D::dot(const Vector3D &other) const
{
  return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::cross(const Vector3D &other) const
{
  return {y * other.z - z * other.y, z * other.x - x * other.z,
          x * other.y - y * other.x};
}

double Vector3D::magnitude() const { return std::sqrt(x * x + y * y + z * z); }

double Vector3D::squaredMagnitude() const { return x * x + y * y + z * z; }

Vector3D Vector3D::normalise() const
{
  double mag = magnitude();
  return (mag == 0.0) ? Vector3D::ZERO : (*this / mag);
}

double Vector3D::distance(const Vector3D &other) const
{
  return (*this - other).magnitude();
}

double Vector3D::angle(const Vector3D &other) const
{
  // cos(theta) = dot_product / (mag1 * mag2)
  double magProduct = magnitude() * other.magnitude();
  return (magProduct == 0.0) ? 0.0 : std::acos(dot(other) / magProduct);
}

Vector3D Vector3D::projectOnto(const Vector3D &other) const
{
  // projection = vec1 * (dot_product / (mag1 * mag2))
  double denom = other.squaredMagnitude();
  return (denom == 0.0) ? Vector3D::ZERO : other * (dot(other) / denom);
}

// ostream (friend)
std::ostream &operator<<(std::ostream &os, const Vector3D &v)
{
  return os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
}