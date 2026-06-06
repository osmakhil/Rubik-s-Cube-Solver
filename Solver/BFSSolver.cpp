#include "BFSSolver.hpp"
#include "../Model/RubiksCube_3DArray.hpp"
#include "../Model/RubiksCube_1DArray.hpp"
#include "../Model/RubiksCube_Bitboard.hpp"
#include <queue>
#include <algorithm>
#include <cassert>

// BFS code to find the solution (helper function)
template <typename T, typename H>
T BFSSolver<T, H>::bfs() {
    std::queue<T> q;
    q.push(rubiksCube);
    visited[rubiksCube] = true;

    while (!q.empty()) {
        T node = q.front();
        q.pop();

        if (node.isSolved()) {
            return node;
        }

        for (int i = 0; i < 18; i++) {
            auto move = RubiksCube::MOVE(i);
            node.move(move);
            if (!visited[node]) {
                visited[node] = true;
                move_done[node] = move;
                q.push(node);
            }
            node.invert(move);
        }
    }
    return rubiksCube;
}

template <typename T, typename H>
BFSSolver<T, H>::BFSSolver(T _rubiksCube) {
    rubiksCube = _rubiksCube;
}

template <typename T, typename H>
std::vector<RubiksCube::MOVE> BFSSolver<T, H>::solve() {
    T solved_cube = bfs();
    assert(solved_cube.isSolved());
    T curr_cube = solved_cube;
    while (!(curr_cube == rubiksCube)) {
        RubiksCube::MOVE curr_move = move_done[curr_cube];
        moves.push_back(curr_move);
        curr_cube.invert(curr_move);
    }
    std::reverse(moves.begin(), moves.end());
    return moves;
}

// Explicit template instantiations
template class BFSSolver<RubiksCube3dArray, Hash3d>;
template class BFSSolver<RubiksCube1dArray, Hash1d>;
template class BFSSolver<RubiksCubeBitboard, HashBitboard>;