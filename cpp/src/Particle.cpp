// Implementation of Particle.hpp

#include "Particle.hpp"
#include "Vector.hpp"

#include <stdexcept>

// Constructor
Particle::Particle(ParticleConstants::ParticleType type_, double energy_,
                   Vector3D &position_, Vector3D &direction_)
{
  // Set before checks
  mass = ParticleConstants::ParticleTypeToMass.at(type_);

  // Checks
  checkEnergy(energy_);
  checkDirection(direction_);

  energy = energy_;
  direction = direction_;
  position = position_;
  type = type_;
  birth_energy = energy;
}

// Setters
void Particle::setEnergy(double energy_)
{
  checkEnergy(energy_);
  energy = energy_;
}

void Particle::setPosition(Vector3D &position_) { position = position_; }

void Particle::setDirection(Vector3D &direction_)
{
  checkDirection(direction_);
  direction = direction_;
}

// Validation
void Particle::checkEnergy(double energy_) const
{
  if(energy_ < mass) // Also checks that energy >= 0 as mass >= 0
  {
    throw std::invalid_argument("Invalid particle energy: energy must be "
                                "greater or equal to particle mass");
  }
}

void Particle::checkDirection(Vector3D &direction_) const
{
  if(direction_.isZero())
  {
    throw std::invalid_argument(
        "Invalid particle direction: direction vector cannot be {0, 0, 0}");
  }
}