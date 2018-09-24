#pragma once
#include <random>

static float get_random_number()
{
  static std::random_device rd;
  static std::mt19937 mt(rd());
  static std::uniform_real_distribution<float> dist(0, 1);
  return dist(mt);
}
