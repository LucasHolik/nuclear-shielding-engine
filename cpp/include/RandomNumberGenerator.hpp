// Random number generator to be used for generating random numbers with
// specified distributions

#pragma once

#include "Material.hpp"
#include "Particle.hpp"

#include <cstdint>
#include <random>

class RandomNumberGenerator
{
private:
  std::mt19937_64 rng;
  std::uint64_t seed;

public:
  // Constructor with explicit seed
  RandomNumberGenerator(std::uint64_t seed_) : seed{seed_}, rng(seed_) {}
  // Default constructor with random seed - uses explicit seed constructor with
  // random seed
  RandomNumberGenerator() : RandomNumberGenerator(std::random_device{}()) {}

  // Getters
  std::uint64_t getSeed() const { return seed; }
  std::mt19937_64 getRNG() const { return rng; }

  // Montecarlo application
  double getRandomStep(const Particle &particle, Material material);
};