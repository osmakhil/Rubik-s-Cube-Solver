#ifndef RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H

#include "../Model/RubiksCube.hpp"
#include "DFSSolver.hpp"
#include <vector>

template <typename T, typename H> class IDDFSSolver {

private:
  int max_search_depth;
  vector<RubiksCube::MOVE> moves;

public:
  T rubiksCube;

  IDDFSSolver(T _rubiksCube, int _max_search_depth);

  vector<RubiksCube::MOVE> solve();
};

#endif