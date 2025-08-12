// Implementation of the DataProcessor class

#include "DataProcessor.hpp"
#include "constants.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

DataProcessor &DataProcessor::getInstance()
{
  static DataProcessor instance;

  return instance;
}

DataProcessor &
DataProcessor::getInstance(ParticleConstants::ParticleType particle_type,
                           ElementConversion::Element element)
{
  DataProcessor &instance{getInstance()};
  instance.addDataSingleFile(particle_type, element);

  return instance;
}

DataProcessor &DataProcessor::getInstance(
    const std::vector<
        std::pair<ParticleConstants::ParticleType, ElementConversion::Element>>
        &particle_element_pairs)
{
  DataProcessor &instance{getInstance()};
  instance.addDataMultipleFiles(particle_element_pairs);

  return instance;
}

void DataProcessor::getDataFromFile(
    std::string &filepath, ParticleConstants::ParticleType particle_type,
    ElementConversion::Element element)
{
  // Cancel if particle and element pair is already in the database
  if(inDatabase(particle_type, element))
  {
    return;
  }

  // Get number of columns in file based off particle type
  auto no_of_columns{FileConstants::ParticleFileColumnNumber.at(particle_type)};

  std::vector<double> cross_section_line;
  std::vector<std::string> cross_section_line_str;

  switch(particle_type)
  {
  case ParticleConstants::ParticleType::GAMMA:

    cross_section_line.resize(no_of_columns);
    cross_section_line_str.resize(no_of_columns);
    break;

  default:

    throw std::invalid_argument("Invalid ParticleType");
  }

  std::ifstream file(filepath);

  int xs_data_start_line{
      FileConstants::ParticleToDataStartLine.at(particle_type)};

  std::string line;
  int line_number{0};
  std::vector<std::vector<double>> cross_sections;

  while(std::getline(file, line))
  {
    line_number += 1;

    // If data hasn't started don't process
    if(line_number < xs_data_start_line)
    {
      continue;
    }

    cross_section_line_str = manualSplit(line, FileConstants::Delimiter);
    cross_section_line =
        stringVecToDoubleVecScientificNotation(cross_section_line_str);

    // Add to 2D cross section array
    cross_sections.push_back(cross_section_line);
  }

  file.close();

  // Add to the data map
  data[particle_type][element] = cross_sections;
  number_data_elements += 1;
}

std::vector<std::string> DataProcessor::manualSplit(const std::string &string,
                                                    char delimiter)
{

  std::vector<std::string> splits;
  std::vector<size_t> delimiter_positions;

  // Find delimiter positions
  for(size_t i{0}; i < string.length(); i++)
  {
    if(string[i] == delimiter)
    {
      delimiter_positions.push_back(i);
    }
  }

  // Split string
  size_t start{0};

  for(size_t delim_pos : delimiter_positions)
  {
    // Extract the individual values
    std::string split{string.substr(start, delim_pos - start)};
    splits.push_back(split);
    start = delim_pos + 1; // Move to start of next split
  }

  return splits;
}

std::vector<double> DataProcessor::stringVecToDoubleVecScientificNotation(
    const std::vector<std::string> &string_vec)
{
  std::vector<double> values;

  for(const auto &part : string_vec)
  {
    values.push_back(std::stod(part));
  }

  return values;
}

std::string
DataProcessor::processFilePath(ParticleConstants::ParticleType particle_type,
                               ElementConversion::Element element)
{
  std::string particle_file_str{FileConstants::ParticleToFilePath.at(
      particle_type)}; // Has ../../[particle_type]/

  std::string element_str{ElementConversion::ElementToSymbol.at(element)};

  int atomic_no{static_cast<int>(element)};
  std::string atomic_no_str{std::to_string(atomic_no)};

  size_t len{atomic_no_str.length()};

  switch(len)
  {
  case 1:

    atomic_no_str = "00" + atomic_no_str;
    break;

  case 2:

    atomic_no_str = "0" + atomic_no_str;
    break;

  case 3:

    break;

  default:

    throw std::runtime_error("Invalid length of atomic number string");
  }

  std::string filepath{particle_file_str + "element_" + atomic_no_str + "_" +
                       element_str + ".txt"};

  return filepath;
}

bool DataProcessor::inDatabase(ParticleConstants::ParticleType particle_type,
                               ElementConversion::Element element)
{
  if(data[particle_type].find(element) !=
     data[particle_type].end()) // If an element for a given particletype is
                                // already in the database then return true
  {
    return true;
  }

  return false;
}

double DataProcessor::interpolateBetween(double value, double a1, double a2,
                                         double b1, double b2) const
{
  if(!(value >= a1 && value <= a2))
  {
    throw std::runtime_error("value must be between a1 and a2 (inclusively)");
  }

  // Transform to log space
  double log_value{std::log(value)};
  double log_a1{std::log(a1)};
  double log_a2{std::log(a2)};
  double log_b1{std::log(b1)};
  double log_b2{std::log(b2)};

  double proportion{(log_value - log_a1) / (log_a2 - log_a1)};
  double log_result{log_b1 + (log_b2 - log_b1) * proportion};

  // Transform back
  double result{std::exp(log_result)};

  return result;
}

bool DataProcessor::isAllowedReaction(
    ParticleConstants::ParticleType particle_type,
    ParticleConstants::ReactionType reaction)
{
  auto particle_it{ParticleConstants::AllowedReactions.find(particle_type)};

  if(particle_it != ParticleConstants::AllowedReactions.end())
  {
    // If in here then there are allowed reactions for the specified particle
    if(particle_it->second.find(reaction) != particle_it->second.end())
    {
      return true;
    }
  }

  return false;
}

const std::pair<size_t, size_t>
DataProcessor::getAboveBelowIndices(double value,
                                    std::vector<double> values) const
{
  // lower_bound gives first element >= target
  auto it{std::lower_bound(values.begin(), values.end(), value)};

  // If energy is too low
  if(it == values.begin())
  {
    // Check for lower bound
    if(value == values[0])
    {
      return std::make_pair(0, 0);
    }
    throw std::runtime_error("Value below range");
  }
  if(it == values.end())
  {
    throw std::runtime_error("Value above range");
  }

  size_t upper_index{static_cast<size_t>(std::distance(values.begin(), it))};

  size_t max_index{values.size() - 1};

  // Edge case: if at a k-edge then value == values[upper_index] ==
  // values[upper_index + 1]
  // First check that we're not at the end
  if(upper_index < max_index)
  {
    // Check for k-edge
    if(value == values[upper_index + 1])
    {
      // At k-edge so return both of the larger indices
      upper_index += 1;

      return std::make_pair(upper_index, upper_index);
    }
  }

  // Also check if value exactly matches
  if(value == values[upper_index])
  {
    return std::make_pair(upper_index, upper_index);
  }

  size_t lower_index{upper_index - 1};

  return std::make_pair(upper_index, lower_index);
}

double
DataProcessor::getAttenCoef(double energy,
                            ParticleConstants::ReactionType reaction,
                            ParticleConstants::ParticleType particle_type,
                            ElementConversion::Element element)
{
  // Files are formatted with energy going low to high and when there are
  // k-edges the photon energy will be duplicated with lower mass attenuation
  // coefs above, hence just have to search for the energy values closest to the
  // energy we're searching and verify that their indices are +-1 of each other.

  // Check that the reaction is allowed
  if(!isAllowedReaction(particle_type, reaction))
  {
    throw std::runtime_error("Invalid reaction: Particle enum " +
                             std::to_string(static_cast<int>(particle_type)) +
                             ", Reaction enum " +
                             std::to_string(static_cast<int>(reaction)));
  }

  const std::vector<std::vector<double>> &data_{
      data.at(particle_type).at(element)}; // Throws if not found

  size_t reaction_column{FileConstants::ReactionToColumn.at(particle_type)
                             .at(reaction)}; // Throws if not found

  std::vector<double> energies;

  for(const std::vector<double> &line : data_)
  {
    energies.push_back(line[FileConstants::EnergyColumn]);
  }

  std::pair<size_t, size_t> above_below_indices{
      getAboveBelowIndices(energy, energies)};

  size_t index1{above_below_indices.second};
  size_t index2{above_below_indices.first};

  // Edge case
  if(index1 == index2)
  {
    return data_[index1][reaction_column];
  }

  double energy1{energies[index1]};
  double energy2{energies[index2]};
  double mass_atten_coef1{data_[index1][reaction_column]};
  double mass_atten_coef2{data_[index2][reaction_column]};

  double interpolated_mass_atten_coef{interpolateBetween(
      energy, energy1, energy2, mass_atten_coef1, mass_atten_coef2)};

  return interpolated_mass_atten_coef;
}

void DataProcessor::addDataSingleFile(
    ParticleConstants::ParticleType particle_type,
    ElementConversion::Element element)
{
  std::string filepath{processFilePath(particle_type, element)};

  getDataFromFile(filepath, particle_type, element);
}

void DataProcessor::addDataMultipleFiles(
    const std::vector<
        std::pair<ParticleConstants::ParticleType, ElementConversion::Element>>
        &particle_element_pairs)
{
  for(const auto &p_e_pair : particle_element_pairs)
  {
    auto particle_type{p_e_pair.first};
    auto element{p_e_pair.second};

    addDataSingleFile(particle_type, element);
  }
}