#ifndef RUBIKS_CUBE_SOLVER_BFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_BFSSOLVER_H

#include "../Model/RubiksCube.hpp"
#include <vector>
#include <unordered_map>

// Typename T: RubiksCube Representation used (3d, 1d, Bitboard)
// Typename H: Corresponding Hash function
template <typename T, typename H>
class BFSSolver {
private:
    std::vector<RubiksCube::MOVE> moves;
    std::unordered_map<T, bool, H> visited;
    std::unordered_map<T, RubiksCube::MOVE, H> move_done;

    // BFS code to find the solution (helper function)
    T bfs();

public:
    T rubiksCube;

    BFSSolver(T _rubiksCube);

    std::vector<RubiksCube::MOVE> solve();
};

#endif // RUBIKS_CUBE_SOLVER_BFSSOLVER_H
