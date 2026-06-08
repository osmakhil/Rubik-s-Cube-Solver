#include "IDAStarSolver.hpp"
#include "../Model/RubiksCube_3DArray.hpp"
#include "../Model/RubiksCube_1DArray.hpp"
#include "../Model/RubiksCube_Bitboard.hpp"
#include <queue>
#include <algorithm>
#include <cassert>

template <typename T, typename H>
void IDAstarSolver<T, H>::resetStructure() {
  moves.clear();
  move_done.clear();
  visited.clear();
}

template <typename T, typename H>
std::pair<T, int> IDAstarSolver<T, H>::IDAstar(int bound) {
  //        priority_queue contains pair(Node, move done to reach that)
  std::priority_queue<std::pair<Node, int>, std::vector<std::pair<Node, int>>, compareCube> pq;
  Node start = Node(rubiksCube, 0, cornerDB.getNumMoves(rubiksCube));
  pq.push(std::make_pair(start, 0));
  int next_bound = 100;
  while (!pq.empty()) {
    auto p = pq.top();
    Node node = p.first;
    pq.pop();

    if (visited[node.cube])
      continue;

    visited[node.cube] = true;
    move_done[node.cube] = RubiksCube::MOVE(p.second);

    if (node.cube.isSolved())
      return std::make_pair(node.cube, bound);
    node.depth++;
    for (int i = 0; i < 18; i++) {
      auto curr_move = RubiksCube::MOVE(i);
      node.cube.move(curr_move);
      if (!visited[node.cube]) {
        node.estimate = cornerDB.getNumMoves(node.cube);
        if (node.estimate + node.depth > bound) {
          next_bound = std::min(next_bound, node.estimate + node.depth);
        } else {
          pq.push(std::make_pair(node, i));
        }
      }
      node.cube.invert(curr_move);
    }
  }
  return std::make_pair(rubiksCube, next_bound);
}

template <typename T, typename H>
IDAstarSolver<T, H>::IDAstarSolver(T _rubiksCube, std::string fileName) {
  rubiksCube = _rubiksCube;
  cornerDB.fromFile(fileName);
}

template <typename T, typename H>
std::vector<RubiksCube::MOVE> IDAstarSolver<T, H>::solve() {
  int bound = 1;
  auto p = IDAstar(bound);
  while (p.second != bound) {
    resetStructure();
    bound = p.second;
    p = IDAstar(bound);
  }
  T solved_cube = p.first;
  assert(solved_cube.isSolved());
  T curr_cube = solved_cube;
  while (!(curr_cube == rubiksCube)) {
    RubiksCube::MOVE curr_move = move_done[curr_cube];
    moves.push_back(curr_move);
    curr_cube.invert(curr_move);
  }
  rubiksCube = solved_cube;
  std::reverse(moves.begin(), moves.end());
  return moves;
}

// Explicit template instantiations
template class IDAstarSolver<RubiksCube3dArray, Hash3d>;
template class IDAstarSolver<RubiksCube1dArray, Hash1d>;
template class IDAstarSolver<RubiksCubeBitboard, HashBitboard>;
