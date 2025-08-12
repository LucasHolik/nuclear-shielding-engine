#include "DataProcessor.hpp"

#include <iostream>

int main()
{

  DataProcessor dp;

  std::string filepath{dp.processFilePath(
      ParticleConstants::ParticleType::GAMMA, ElementConversion::Element::C)};

  std::cout << filepath;

  return 0;
}