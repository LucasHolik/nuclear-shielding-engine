// Implementation of the DataProcessor class

#include "DataProcessor.hpp"
#include "constants.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

DataProcessor::DataProcessor(ParticleConstants::ParticleType particle_type,
                             ElementConversion::Element element)
{}

void DataProcessor::getDataFromFile(
    std::string &filepath, ParticleConstants::ParticleType particle_type,
    ElementConversion::Element element)
{
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