// Processes cross section data from the data folder

#pragma once

#include "Constants.hpp"

#include <array>
#include <map>
#include <vector>

// Cached data stored in a map linking each particle to an element and its cross
// section data
using XsData =
    std::unordered_map<ParticleConstants::ParticleType,
                       std::unordered_map<ElementConversion::Element,
                                          std::vector<std::vector<double>>>>;

class DataProcessor
{
private:
  XsData data;

  void getDataFromFile(
      std::string &filepath, ParticleConstants::ParticleType particle_type,
      ElementConversion::Element element); // Stores filedata in data

  std::vector<std::string> manualSplit(const std::string &string,
                                       char delimiter);

  std::vector<double> stringVecToDoubleVecScientificNotation(
      const std::vector<std::string> &string_vec);

public:
  // Empty Constructor
  DataProcessor() {};
  // Constructor with a particle and element
  DataProcessor(ParticleConstants::ParticleType particle_type,
                ElementConversion::Element element);
  // Getters
  XsData getData() const { return data; }
  std::string processFilePath(ParticleConstants::ParticleType particle_type,
                              ElementConversion::Element element);
  //
};