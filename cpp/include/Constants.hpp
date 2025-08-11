// File containing all hardcoded constants required for the project
// Using natural units (c=1) throughout this project

#pragma once

#include <map>
#include <string>

namespace ParticleConstants
{

// Particle type enum
enum class ParticleType
{
  GAMMA = 0,
  NEUTRON = 1,
  PROTON = 2
};

// Map ParticleType to name
inline const std::map<ParticleType, std::string> ParticleTypeToName{
    {ParticleType::GAMMA, "gamma"},
    {ParticleType::NEUTRON, "neutron"},
    {ParticleType::PROTON, "proton"}};

// Map ParticleType to mass in MeV
inline const std::map<ParticleType, double> ParticleTypeToMass{
    {ParticleType::GAMMA, 0},
    {ParticleType::NEUTRON, 939.56542194},
    {ParticleType::PROTON, 938.27208816}};

} // namespace ParticleConstants