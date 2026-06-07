#ifndef RUBIKS_CUBE_SOLVER_CORNERPATTERNDATABASE_H
#define RUBIKS_CUBE_SOLVER_CORNERPATTERNDATABASE_H

#include "../Model/RubiksCube.hpp"
#include "PatternDatabase.hpp"
#include "PermutationIndexer.hpp"
using namespace std;

class CornerPatternDatabase : public PatternDatabase {

  typedef RubiksCube::FACE F;

  PermutationIndexer<8> permIndexer;

public:
  CornerPatternDatabase();
  CornerPatternDatabase(uint8_t init_val);
  uint32_t getDatabaseIndex(const RubiksCube &cube) const;
};
#endif