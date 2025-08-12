#include "DataProcessor.hpp"

#include <iostream>
#include <vector>

int main()
{

  DataProcessor dp{DataProcessor::getInstance(
      ParticleConstants::ParticleType::GAMMA, ElementConversion::Element::Sn)};

  std::cout << "Enter photon energy (MeV): \n";

  double energy;

  std::cin >> energy;

  double attencoef{dp.getAttenCoef(
      energy, ParticleConstants::ReactionType::PHOTOELECTRIC_ABSORPTION,
      ParticleConstants::ParticleType::GAMMA, ElementConversion::Element::Sn)};

  std::cout << attencoef << "\n";

  return 0;
}