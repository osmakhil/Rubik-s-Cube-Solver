#include "DFSSolver.hpp"
#include "../Model/RubiksCube_3DArray.hpp"
#include "../Model/RubiksCube_1DArray.hpp"
#include "../Model/RubiksCube_Bitboard.hpp"

// DFS code to find the solution (helper function)
template <typename T, typename H>
bool DFSSolver<T, H>::dfs(int dep) {
    if (rubiksCube.isSolved())
        return true;
    if (dep > max_search_depth)
        return false;

    for (int i = 0; i < 18; i++) {
        rubiksCube.move(RubiksCube::MOVE(i));
        moves.push_back(RubiksCube::MOVE(i));
        if (dfs(dep + 1))
            return true;
        moves.pop_back();
        rubiksCube.invert(RubiksCube::MOVE(i));
    }
    return false;
}

template <typename T, typename H>
DFSSolver<T, H>::DFSSolver(T _rubiksCube, int _max_search_depth) {
    rubiksCube = _rubiksCube;
    max_search_depth = _max_search_depth;
}

template <typename T, typename H>
std::vector<RubiksCube::MOVE> DFSSolver<T, H>::solve() {
    dfs(1);
    return moves;
}

// Explicit template instantiations
template class DFSSolver<RubiksCube3dArray, Hash3d>;
template class DFSSolver<RubiksCube1dArray, Hash1d>;
template class DFSSolver<RubiksCubeBitboard, HashBitboard>;