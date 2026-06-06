#include "IDDFSSolver.hpp"
#include "../Model/RubiksCube_1DArray.hpp"
#include "../Model/RubiksCube_3DArray.hpp"
#include "../Model/RubiksCube_Bitboard.hpp"
#include <vector>
template <typename T, typename H>
IDDFSSolver<T, H>::IDDFSSolver(T _rubiksCube, int _max_search_depth) {
  rubiksCube = _rubiksCube;
  max_search_depth = _max_search_depth;
}

template <typename T, typename H>
std::vector<RubiksCube::MOVE> IDDFSSolver<T, H>::solve() {

  for (int i = 1; i <= max_search_depth; i++) {
    DFSSolver<T, H> dfsSolver(rubiksCube, i);
    moves = dfsSolver.solve();
    if (dfsSolver.rubiksCube.isSolved()) {
      rubiksCube = dfsSolver.rubiksCube;
      break;
    }
  }
  return moves;
}

// Explicit template instantiations
template class IDDFSSolver<RubiksCube3dArray, Hash3d>;
template class IDDFSSolver<RubiksCube1dArray, Hash1d>;
template class IDDFSSolver<RubiksCubeBitboard, HashBitboard>;