// Processes cross section data from the data folder
// Singleton design pattern

#pragma once

#include "Constants.hpp"

#include <array>
#include <map>
#include <span>
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

  int number_data_elements;

  // Empty Constructor
  DataProcessor() : number_data_elements{0} {}

  void getDataFromFile(
      std::string &filepath, ParticleConstants::ParticleType particle_type,
      ElementConversion::Element element); // Stores filedata in data

  std::vector<std::string> manualSplit(const std::string &string,
                                       char delimiter);

  std::vector<double> stringVecToDoubleVecScientificNotation(
      const std::vector<std::string> &string_vec);

  std::string processFilePath(ParticleConstants::ParticleType particle_type,
                              ElementConversion::Element element);

  bool inDatabase(ParticleConstants::ParticleType particle_type,
                  ElementConversion::Element element);

  // Log-log interpolatation between b1 and b2 based off how far value is
  // between a1 and a2
  double interpolateBetween(double value, double a1, double a2, double b1,
                            double b2) const;

  void checkReaction(ParticleConstants::ParticleType particle_type,
                     ParticleConstants::ReactionType reaction);

  const std::pair<size_t, size_t>
  getAboveBelowIndices(double value, std::vector<double> values)
      const; // Returns std::pair(upper_index, lower_index)

public:
  // Singleton access
  static DataProcessor &getInstance();
  static DataProcessor &
  getInstance(ParticleConstants::ParticleType particle_type,
              ElementConversion::Element element);
  static DataProcessor &
  getInstance(const std::vector<std::pair<ParticleConstants::ParticleType,
                                          ElementConversion::Element>>
                  &particle_element_pairs);

  // Getters
  const XsData &getAllData() const { return data; }
  int get_number_data_elements() const { return number_data_elements; }
  const std::vector<std::vector<double>> &
  getData(ParticleConstants::ParticleType particle_type,
          ElementConversion::Element element)
  {
    return data.at(particle_type).at(element); // Throws if not found
  }
  const double getAttenCoef(double energy,
                            ParticleConstants::ReactionType reaction,
                            ParticleConstants::ParticleType particle_type,
                            ElementConversion::Element element);
  const std::vector<double>
  getAllAttenCoefs(double energy, ParticleConstants::ParticleType particle_type,
                   ElementConversion::Element element);

  // Add data
  void addDataSingleFile(ParticleConstants::ParticleType particle_type,
                         ElementConversion::Element element);

  void addDataMultipleFiles(
      const std::vector<std::pair<ParticleConstants::ParticleType,
                                  ElementConversion::Element>>
          &particle_element_pairs);
};