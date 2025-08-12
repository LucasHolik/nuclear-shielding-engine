#include "DataProcessor.hpp"

#include <iostream>
#include <vector>

int main()
{

  DataProcessor dp{DataProcessor::getInstance()};

  dp.addDataSingleFile(ParticleConstants::ParticleType::GAMMA,
                       ElementConversion::Element::C);

  std::vector<
      std::pair<ParticleConstants::ParticleType, ElementConversion::Element>>
      particle_element_list;

  particle_element_list.push_back(std::make_pair(
      ParticleConstants::ParticleType::GAMMA, ElementConversion::Element::Ac));
  particle_element_list.push_back(std::make_pair(
      ParticleConstants::ParticleType::GAMMA, ElementConversion::Element::P));
  particle_element_list.push_back(std::make_pair(
      ParticleConstants::ParticleType::GAMMA, ElementConversion::Element::C));

  dp.addDataMultipleFiles(particle_element_list);

  std::cout << dp.get_number_data_elements() << "\n";

  auto data{dp.getData(ParticleConstants::ParticleType::GAMMA,
                       ElementConversion::Element::C)};

  for(auto &vec : data)
  {
    for(double num : vec)
    {
      std::cout << num << "\n";
    }
  }

  return 0;
}