#include "Model/RubiksCube_3DArray.hpp"
#include "Model/RubiksCube_Bitboard.hpp"
#include "Solver/BFSSolver.hpp"
#include "Solver/DFSSolver.hpp"
#include "Solver/IDDFSSolver.hpp"
#include <iostream>

using namespace std;

int main() {

  RubiksCubeBitboard cube;

  // Shuffle cube
  auto moves = cube.randomShuffleCube(10);
  cout << "Shuffle moves (" << moves.size() << "): ";
  for (auto mov : moves) {
    cout << cube.getMove(mov) << " ";
  }
  cout << "\n";

  cube.print();

  // // DFS Solver
  // cout << "\n[DFS Solving]\n";
  // DFSSolver<RubiksCube3dArray, Hash3d> dfsSolver(cube, 5);
  // auto dfsSolution = dfsSolver.solve();
  // cout << "DFS Moves found (" << dfsSolution.size() << "): ";
  // for (auto m : dfsSolution)
  //   cout << cube.getMove(m) << " ";
  // cout << "\n";

  // // BFS Solver
  // cout << "\n[BFS Solving]\n";
  // BFSSolver<RubiksCubeBitboard, HashBitboard> bfsSolver(cube);
  // auto bfsSolution = bfsSolver.solve();
  // cout << "BFS Moves found (" << bfsSolution.size() << "): ";
  // for (auto m : bfsSolution)
  //   cout << cube.getMove(m) << " ";
  // cout << "\n";

  // IDDFS Solver
  cout << "\n[IDDFS Solving]\n";
  IDDFSSolver<RubiksCubeBitboard, HashBitboard> iddfsSolver(cube, 7);
  auto iddfsSolution = iddfsSolver.solve();
  cout << "IDDFS Moves found (" << iddfsSolution.size() << "): ";
  for (auto m : iddfsSolution)
    cout << cube.getMove(m) << " ";
  cout << "\n";

  // Apply the moves to the cube to solve it
  for (auto m : iddfsSolution)
    cube.move(m);

  cube.print();
}