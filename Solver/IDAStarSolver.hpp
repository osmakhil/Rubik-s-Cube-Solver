
#include "../Model/RubiksCube.hpp"
#include <unordered_map>
#include <vector>
// #include "../Model/PatternDatabase/PatternDatabase.h"
#include "../PatternDatabase/CornerPatternDatabase.hpp"

#ifndef RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H

template <typename T, typename H> class IDAstarSolver {
private:
  CornerPatternDatabase cornerDB;
  vector<RubiksCube::MOVE> moves;
  unordered_map<T, RubiksCube::MOVE, H> move_done;
  unordered_map<T, bool, H> visited;

  struct Node {
    T cube;
    int depth;
    int estimate;

    Node(T _cube, int _depth, int _estimate)
        : cube(_cube), depth(_depth), estimate(_estimate) {};
  };

  struct compareCube {
    bool operator()(pair<Node, int> const &p1, pair<Node, int> const &p2) {
      auto n1 = p1.first, n2 = p2.first;
      if (n1.depth + n1.estimate == n2.depth + n2.estimate) {
        return n1.estimate > n2.estimate;
      } else
        return n1.depth + n1.estimate > n2.depth + n2.estimate;
    }
  };

  void resetStructure();

  // returns {solved cube, bound}: if the cube was solved
  // returns {rubiksCube, next_bound}, if the cube was not solved
  pair<T, int> IDAstar(int bound);

public:
  T rubiksCube;

  IDAstarSolver(T _rubiksCube, string fileName);

  vector<RubiksCube::MOVE> solve();
};

#endif // RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H