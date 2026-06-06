#ifndef RUBIKS_CUBE_SOLVER_DFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_DFSSOLVER_H

#include "../Model/RubiksCube.hpp"
#include <vector>

// Typename T: RubiksCube Representation used (3d, 1d, Bitboard)
// Typename H: Corresponding Hash function
template <typename T, typename H>
class DFSSolver {
private:
    std::vector<RubiksCube::MOVE> moves;
    int max_search_depth;

    // DFS code to find the solution (helper function)
    bool dfs(int dep);

public:
    T rubiksCube;

    DFSSolver(T _rubiksCube, int _max_search_depth = 8);

    std::vector<RubiksCube::MOVE> solve();
};

#endif // RUBIKS_CUBE_SOLVER_DFSSOLVER_H
