// Element class

#pragma once

#include "Constants.hpp"
#include "Particle.hpp"
#include <array>
#include <vector>

class Element
{
private:
  double atomic_mass; // amu
  int atomic_number;
  std::vector<std::vector<double>> cross_section_data;
  double density; // g / cm^3 at RTP
  int no_of_cross_section_values;
  ElementConversion::Element type;

public:
  // Constructor
  Element(ElementConversion::Element type_)
      : type{type_}, atomic_number{static_cast<int>(type)},
        atomic_mass{ElementConversion::ElementalMasses.at(type_)}
  {}

  // Getters
  double get_atomic_mass() const { return atomic_mass; }
  int get_atomic_number() const { return atomic_number; }
  std::vector<std::vector<double>> get_cross_section_data() const
  {
    return cross_section_data;
  }
  double get_density() const { return density; }
  int get_no_of_cross_section_values() const
  {
    return no_of_cross_section_values;
  }
  ElementConversion::Element get_type() const { return type; }

  double get_cross_section(Particle &particle, )
};