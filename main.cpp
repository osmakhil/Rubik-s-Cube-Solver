#include "Model/RubiksCube_3DArray.hpp"
#include "Solver/DFSSolver.hpp"
#include "Solver/BFSSolver.hpp"

#include <iostream>

using namespace std;

int main() {

  RubiksCube3dArray cube;

  // Shuffle cube
  auto moves = cube.randomShuffleCube(4);
  cout << "Shuffle moves (" << moves.size() << "): ";
  for (auto mov : moves) {
    cout << cube.getMove(mov) << " ";
  }
  cout << "\n";

  cube.print();

  // DFS Solver
  cout << "\n[DFS Solving]\n";
  DFSSolver<RubiksCube3dArray, Hash3d> dfsSolver(cube, 5);
  auto dfsSolution = dfsSolver.solve();
  cout << "DFS Moves found (" << dfsSolution.size() << "): ";
  for (auto m : dfsSolution)
    cout << cube.getMove(m) << " ";
  cout << "\n";

  // BFS Solver
  cout << "\n[BFS Solving]\n";
  BFSSolver<RubiksCube3dArray, Hash3d> bfsSolver(cube);
  auto bfsSolution = bfsSolver.solve();
  cout << "BFS Moves found (" << bfsSolution.size() << "): ";
  for (auto m : bfsSolution)
    cout << cube.getMove(m) << " ";
  cout << "\n";
}