// File containing all hardcoded constants required for the project
// Using natural units (c=1) throughout this project

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

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
inline const std::unordered_map<ParticleType, std::string> ParticleTypeToName{
    {ParticleType::GAMMA, "gamma"},
    {ParticleType::NEUTRON, "neutron"},
    {ParticleType::PROTON, "proton"}};

// Map ParticleType to mass in MeV
inline const std::unordered_map<ParticleType, double> ParticleTypeToMass{
    {ParticleType::GAMMA, 0},
    {ParticleType::NEUTRON, 939.56542194},
    {ParticleType::PROTON, 938.27208816}};

enum class ReactionType
{
  COHERENT_SCATTERING = 0,
  INCOHERENT_SCATTERING = 1,
  PHOTOELECTRIC_ABSORPTION = 2,
  NUCLEAR_PAIR_PRODUCTION = 3,
  ELECTRON_PAIR_PRODUCTION = 4,
  TOTAL_WITH_COHERENT = 5,
  TOTAL_WITHOUT_COHERENT = 6
};

inline const std::unordered_map<ParticleType, std::unordered_set<ReactionType>>
    AllowedReactions{{ParticleType::GAMMA,
                      {ReactionType::COHERENT_SCATTERING,
                       ReactionType::INCOHERENT_SCATTERING,
                       ReactionType::PHOTOELECTRIC_ABSORPTION}}};

} // namespace ParticleConstants

namespace FileConstants
{
inline const char Delimiter{' '};

inline const int EnergyColumn{0};

inline const std::unordered_map<ParticleConstants::ParticleType, std::string>
    ParticleToFilePath{
        {ParticleConstants::ParticleType::GAMMA, "data/photon/"}};

inline const std::unordered_map<std::string, ParticleConstants::ParticleType>
    FilePathToParticle{
        {"data/photon/", ParticleConstants::ParticleType::GAMMA}};

inline const std::unordered_map<ParticleConstants::ParticleType, int>
    ParticleFileColumnNumber{{ParticleConstants::ParticleType::GAMMA, 8}};

inline const std::unordered_map<ParticleConstants::ParticleType, int>
    ParticleToDataStartLine{{ParticleConstants::ParticleType::GAMMA, 4}};

inline const std::unordered_map<
    ParticleConstants::ParticleType,
    std::unordered_map<ParticleConstants::ReactionType, size_t>>
    ReactionToColumn{
        {ParticleConstants::ParticleType::GAMMA,
         {{ParticleConstants::ReactionType::COHERENT_SCATTERING, 1},
          {ParticleConstants::ReactionType::INCOHERENT_SCATTERING, 2},
          {ParticleConstants::ReactionType::PHOTOELECTRIC_ABSORPTION, 3},
          {ParticleConstants::ReactionType::NUCLEAR_PAIR_PRODUCTION, 4},
          {ParticleConstants::ReactionType::ELECTRON_PAIR_PRODUCTION, 5},
          {ParticleConstants::ReactionType::TOTAL_WITH_COHERENT, 6},
          {ParticleConstants::ReactionType::TOTAL_WITHOUT_COHERENT, 7}}}};
} // namespace FileConstants

namespace ElementConversion
{
enum class Element
{
  // Period 1
  H = 1,  // Hydrogen
  He = 2, // Helium

  // Period 2
  Li = 3,  // Lithium
  Be = 4,  // Beryllium
  B = 5,   // Boron
  C = 6,   // Carbon
  N = 7,   // Nitrogen
  O = 8,   // Oxygen
  F = 9,   // Fluorine
  Ne = 10, // Neon

  // Period 3
  Na = 11, // Sodium
  Mg = 12, // Magnesium
  Al = 13, // Aluminium
  Si = 14, // Silicon
  P = 15,  // Phosphorus
  S = 16,  // Sulfur
  Cl = 17, // Chlorine
  Ar = 18, // Argon

  // Period 4
  K = 19,  // Potassium
  Ca = 20, // Calcium
  Sc = 21, // Scandium
  Ti = 22, // Titanium
  V = 23,  // Vanadium
  Cr = 24, // Chromium
  Mn = 25, // Manganese
  Fe = 26, // Iron
  Co = 27, // Cobalt
  Ni = 28, // Nickel
  Cu = 29, // Copper
  Zn = 30, // Zinc
  Ga = 31, // Gallium
  Ge = 32, // Germanium
  As = 33, // Arsenic
  Se = 34, // Selenium
  Br = 35, // Bromine
  Kr = 36, // Krypton

  // Period 5
  Rb = 37, // Rubidium
  Sr = 38, // Strontium
  Y = 39,  // Yttrium
  Zr = 40, // Zirconium
  Nb = 41, // Niobium
  Mo = 42, // Molybdenum
  Tc = 43, // Technetium
  Ru = 44, // Ruthenium
  Rh = 45, // Rhodium
  Pd = 46, // Palladium
  Ag = 47, // Silver
  Cd = 48, // Cadmium
  In = 49, // Indium
  Sn = 50, // Tin
  Sb = 51, // Antimony
  Te = 52, // Tellurium
  I = 53,  // Iodine
  Xe = 54, // Xenon

  // Period 6
  Cs = 55, // Caesium
  Ba = 56, // Barium
  La = 57, // Lanthanum
  Ce = 58, // Cerium
  Pr = 59, // Praseodymium
  Nd = 60, // Neodymium
  Pm = 61, // Promethium
  Sm = 62, // Samarium
  Eu = 63, // Europium
  Gd = 64, // Gadolinium
  Tb = 65, // Terbium
  Dy = 66, // Dysprosium
  Ho = 67, // Holmium
  Er = 68, // Erbium
  Tm = 69, // Thulium
  Yb = 70, // Ytterbium
  Lu = 71, // Lutetium
  Hf = 72, // Hafnium
  Ta = 73, // Tantalum
  W = 74,  // Tungsten
  Re = 75, // Rhenium
  Os = 76, // Osmium
  Ir = 77, // Iridium
  Pt = 78, // Platinum
  Au = 79, // Gold
  Hg = 80, // Mercury
  Tl = 81, // Thallium
  Pb = 82, // Lead
  Bi = 83, // Bismuth
  Po = 84, // Polonium
  At = 85, // Astatine
  Rn = 86, // Radon

  // Period 7
  Fr = 87, // Francium
  Ra = 88, // Radium
  Ac = 89, // Actinium
  Th = 90, // Thorium
  Pa = 91, // Protactinium
  U = 92,  // Uranium
  Np = 93, // Neptunium
  Pu = 94, // Plutonium
  Am = 95, // Americium
  Cm = 96, // Curium
  Bk = 97, // Berkelium
  Cf = 98, // Californium
  Es = 99, // Einsteinium
  Fm = 100 // Fermium
};

inline const std::unordered_map<Element, double> ElementalMasses{
    {Element::H, 1.008},   {Element::He, 4.0026}, {Element::Li, 6.94},
    {Element::Be, 9.0122}, {Element::B, 10.81},   {Element::C, 12.011},
    {Element::N, 14.007},  {Element::O, 15.999},  {Element::F, 18.998},
    {Element::Ne, 20.180}, {Element::Na, 22.990}, {Element::Mg, 24.305},
    {Element::Al, 26.982}, {Element::Si, 28.085}, {Element::P, 30.974},
    {Element::S, 32.06},   {Element::Cl, 35.45},  {Element::Ar, 39.948},
    {Element::K, 39.098},  {Element::Ca, 40.078}, {Element::Sc, 44.956},
    {Element::Ti, 47.867}, {Element::V, 50.942},  {Element::Cr, 51.996},
    {Element::Mn, 54.938}, {Element::Fe, 55.845}, {Element::Co, 58.933},
    {Element::Ni, 58.693}, {Element::Cu, 63.546}, {Element::Zn, 65.38},
    {Element::Ga, 69.723}, {Element::Ge, 72.630}, {Element::As, 74.922},
    {Element::Se, 78.971}, {Element::Br, 79.904}, {Element::Kr, 83.798},
    {Element::Rb, 85.468}, {Element::Sr, 87.62},  {Element::Y, 88.906},
    {Element::Zr, 91.224}, {Element::Nb, 92.906}, {Element::Mo, 95.95},
    {Element::Tc, 98.0},   {Element::Ru, 101.07}, {Element::Rh, 102.91},
    {Element::Pd, 106.42}, {Element::Ag, 107.87}, {Element::Cd, 112.41},
    {Element::In, 114.82}, {Element::Sn, 118.71}, {Element::Sb, 121.76},
    {Element::Te, 127.60}, {Element::I, 126.90},  {Element::Xe, 131.29},
    {Element::Cs, 132.91}, {Element::Ba, 137.33}, {Element::La, 138.91},
    {Element::Ce, 140.12}, {Element::Pr, 140.91}, {Element::Nd, 144.24},
    {Element::Pm, 145.0},  {Element::Sm, 150.36}, {Element::Eu, 151.96},
    {Element::Gd, 157.25}, {Element::Tb, 158.93}, {Element::Dy, 162.50},
    {Element::Ho, 164.93}, {Element::Er, 167.26}, {Element::Tm, 168.93},
    {Element::Yb, 173.05}, {Element::Lu, 174.97}, {Element::Hf, 178.49},
    {Element::Ta, 180.95}, {Element::W, 183.84},  {Element::Re, 186.21},
    {Element::Os, 190.23}, {Element::Ir, 192.22}, {Element::Pt, 195.08},
    {Element::Au, 196.97}, {Element::Hg, 200.59}, {Element::Tl, 204.38},
    {Element::Pb, 207.2},  {Element::Bi, 208.98}, {Element::Po, 209.0},
    {Element::At, 210.0},  {Element::Rn, 222.0},  {Element::Fr, 223.0},
    {Element::Ra, 226.0},  {Element::Ac, 227.0},  {Element::Th, 232.04},
    {Element::Pa, 231.04}, {Element::U, 238.03},  {Element::Np, 237.0},
    {Element::Pu, 244.0},  {Element::Am, 243.0},  {Element::Cm, 247.0},
    {Element::Bk, 247.0},  {Element::Cf, 251.0},  {Element::Es, 252.0},
    {Element::Fm, 257.0}}; // amu

const std::unordered_map<Element, std::string> ElementToSymbol{
    // Period 1
    {Element::H, "H"},   // Hydrogen
    {Element::He, "He"}, // Helium

    // Period 2
    {Element::Li, "Li"}, // Lithium
    {Element::Be, "Be"}, // Beryllium
    {Element::B, "B"},   // Boron
    {Element::C, "C"},   // Carbon
    {Element::N, "N"},   // Nitrogen
    {Element::O, "O"},   // Oxygen
    {Element::F, "F"},   // Fluorine
    {Element::Ne, "Ne"}, // Neon

    // Period 3
    {Element::Na, "Na"}, // Sodium
    {Element::Mg, "Mg"}, // Magnesium
    {Element::Al, "Al"}, // Aluminium
    {Element::Si, "Si"}, // Silicon
    {Element::P, "P"},   // Phosphorus
    {Element::S, "S"},   // Sulfur
    {Element::Cl, "Cl"}, // Chlorine
    {Element::Ar, "Ar"}, // Argon

    // Period 4
    {Element::K, "K"},   // Potassium
    {Element::Ca, "Ca"}, // Calcium
    {Element::Sc, "Sc"}, // Scandium
    {Element::Ti, "Ti"}, // Titanium
    {Element::V, "V"},   // Vanadium
    {Element::Cr, "Cr"}, // Chromium
    {Element::Mn, "Mn"}, // Manganese
    {Element::Fe, "Fe"}, // Iron
    {Element::Co, "Co"}, // Cobalt
    {Element::Ni, "Ni"}, // Nickel
    {Element::Cu, "Cu"}, // Copper
    {Element::Zn, "Zn"}, // Zinc
    {Element::Ga, "Ga"}, // Gallium
    {Element::Ge, "Ge"}, // Germanium
    {Element::As, "As"}, // Arsenic
    {Element::Se, "Se"}, // Selenium
    {Element::Br, "Br"}, // Bromine
    {Element::Kr, "Kr"}, // Krypton

    // Period 5
    {Element::Rb, "Rb"}, // Rubidium
    {Element::Sr, "Sr"}, // Strontium
    {Element::Y, "Y"},   // Yttrium
    {Element::Zr, "Zr"}, // Zirconium
    {Element::Nb, "Nb"}, // Niobium
    {Element::Mo, "Mo"}, // Molybdenum
    {Element::Tc, "Tc"}, // Technetium
    {Element::Ru, "Ru"}, // Ruthenium
    {Element::Rh, "Rh"}, // Rhodium
    {Element::Pd, "Pd"}, // Palladium
    {Element::Ag, "Ag"}, // Silver
    {Element::Cd, "Cd"}, // Cadmium
    {Element::In, "In"}, // Indium
    {Element::Sn, "Sn"}, // Tin
    {Element::Sb, "Sb"}, // Antimony
    {Element::Te, "Te"}, // Tellurium
    {Element::I, "I"},   // Iodine
    {Element::Xe, "Xe"}, // Xenon

    // Period 6
    {Element::Cs, "Cs"}, // Caesium
    {Element::Ba, "Ba"}, // Barium
    {Element::La, "La"}, // Lanthanum
    {Element::Ce, "Ce"}, // Cerium
    {Element::Pr, "Pr"}, // Praseodymium
    {Element::Nd, "Nd"}, // Neodymium
    {Element::Pm, "Pm"}, // Promethium
    {Element::Sm, "Sm"}, // Samarium
    {Element::Eu, "Eu"}, // Europium
    {Element::Gd, "Gd"}, // Gadolinium
    {Element::Tb, "Tb"}, // Terbium
    {Element::Dy, "Dy"}, // Dysprosium
    {Element::Ho, "Ho"}, // Holmium
    {Element::Er, "Er"}, // Erbium
    {Element::Tm, "Tm"}, // Thulium
    {Element::Yb, "Yb"}, // Ytterbium
    {Element::Lu, "Lu"}, // Lutetium
    {Element::Hf, "Hf"}, // Hafnium
    {Element::Ta, "Ta"}, // Tantalum
    {Element::W, "W"},   // Tungsten
    {Element::Re, "Re"}, // Rhenium
    {Element::Os, "Os"}, // Osmium
    {Element::Ir, "Ir"}, // Iridium
    {Element::Pt, "Pt"}, // Platinum
    {Element::Au, "Au"}, // Gold
    {Element::Hg, "Hg"}, // Mercury
    {Element::Tl, "Tl"}, // Thallium
    {Element::Pb, "Pb"}, // Lead
    {Element::Bi, "Bi"}, // Bismuth
    {Element::Po, "Po"}, // Polonium
    {Element::At, "At"}, // Astatine
    {Element::Rn, "Rn"}, // Radon

    // Period 7
    {Element::Fr, "Fr"}, // Francium
    {Element::Ra, "Ra"}, // Radium
    {Element::Ac, "Ac"}, // Actinium
    {Element::Th, "Th"}, // Thorium
    {Element::Pa, "Pa"}, // Protactinium
    {Element::U, "U"},   // Uranium
    {Element::Np, "Np"}, // Neptunium
    {Element::Pu, "Pu"}, // Plutonium
    {Element::Am, "Am"}, // Americium
    {Element::Cm, "Cm"}, // Curium
    {Element::Bk, "Bk"}, // Berkelium
    {Element::Cf, "Cf"}, // Californium
    {Element::Es, "Es"}, // Einsteinium
    {Element::Fm, "Fm"}  // Fermium
};

} // namespace ElementConversion