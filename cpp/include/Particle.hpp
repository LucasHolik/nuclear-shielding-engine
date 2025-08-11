// Abstract base particle class containing general methods that implemented
// particles will use polymorphically

#pragma once

#include "Constants.hpp"
#include "Vector.hpp"

#include <string>
#include <vector>

class Particle
{
private:
  double mass;         // MeV
  double energy;       // MeV
  double birth_energy; // Energy when first created
  int id;              // Unique particle identifier
  Vector3D position;
  Vector3D direction;
  ParticleConstants::ParticleType type;
  std::vector<Vector3D> interaction_points;

public:
  // Constructor
  Particle(ParticleConstants::ParticleType type_, double energy_,
           Vector3D &position_, Vector3D &direction_);

  // Getters
  double getMass() const { return mass; }
  double getEnergy() const { return energy; }
  double getBirthEnergy() const { return birth_energy; }
  int getID() const { return id; }
  Vector3D getPosition() const { return position; }
  Vector3D getDirection() const { return direction; }
  ParticleConstants::ParticleType getType() const { return type; }
  double getKE() const { return energy - mass; }
  std::string getName() const
  {
    return ParticleConstants::ParticleTypeToName.at(type);
  }

  // Setters
  void setEnergy(double energy_);
  void setPosition(Vector3D &position_);
  void setDirection(Vector3D &direction_);

  // Validation
  void checkEnergy(double energy_) const;
  void checkDirection(Vector3D &direction_) const;
};