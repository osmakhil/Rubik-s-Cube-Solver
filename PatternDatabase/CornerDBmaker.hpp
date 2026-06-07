
#ifndef RUBIKS_CUBE_SOLVER_CORNERDBMAKER_H
#define RUBIKS_CUBE_SOLVER_CORNERDBMAKER_H
#include "../Model/RubiksCube_Bitboard.hpp"
#include "CornerPatternDatabase.hpp"

using namespace std;

class CornerDBmaker {
private:
  string fileName;
  CornerPatternDatabase cornerDB;

public:
  CornerDBmaker(string _fileName);
  CornerDBmaker(string _fileName, uint8_t init_val);

  bool bfsAndStore();
};

#endif