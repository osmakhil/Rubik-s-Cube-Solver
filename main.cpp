#include "Model/RubiksCube_3DArray.hpp"
#include "Model/RubiksCube_Bitboard.hpp"
#include "Solver/BFSSolver.hpp"
#include "Solver/DFSSolver.hpp"
#include "Solver/IDAStarSolver.hpp"
#include "Solver/IDDFSSolver.hpp"
#include <iostream>

using namespace std;

int main() {
  RubiksCubeBitboard cube;

  // Shuffle cube with 10 random moves
  auto moves = cube.randomShuffleCube(10);
  cout << "Shuffle moves (" << moves.size() << "): ";
  for (auto mov : moves) {
    cout << cube.getMove(mov) << " ";
  }
  cout << "\n\n";

  cube.print();

  // 1. IDDFS Solver
  // cout << "\n[IDDFS Solving]\n";
  // RubiksCubeBitboard cubeIDDFS = cube;
  // IDDFSSolver<RubiksCubeBitboard, HashBitboard> iddfsSolver(cubeIDDFS, 7);
  // auto iddfsSolution = iddfsSolver.solve();
  // cout << "IDDFS Moves found (" << iddfsSolution.size() << "): ";
  // for (auto m : iddfsSolution)
  //   cout << cubeIDDFS.getMove(m) << " ";
  // cout << "\n";

  // // Apply the moves to the copy to verify it solves the cube
  // for (auto m : iddfsSolution)
  //   cubeIDDFS.move(m);

  // if (cubeIDDFS.isSolved()) {
  //   cout << "IDDFS Solved successfully!" << endl;
  // } else {
  //   cout << "IDDFS Failed to solve." << endl;
  // }

  // 2. IDA* Solver (using the precomputed pattern database)
  cout << "\n[IDA* Solving]\n";
  RubiksCubeBitboard cubeIDAStar = cube;
  IDAstarSolver<RubiksCubeBitboard, HashBitboard> idastarSolver(
      cubeIDAStar, "PatternDatabase/cornerDepth8.dat");
  auto idastarSolution = idastarSolver.solve();
  cout << "IDA* Moves found (" << idastarSolution.size() << "): ";
  for (auto m : idastarSolution)
    cout << cubeIDAStar.getMove(m) << " ";
  cout << "\n";

  // Apply the moves to the copy to verify it solves the cube
  for (auto m : idastarSolution)
    cubeIDAStar.move(m);

  if (cubeIDAStar.isSolved()) {
    cout << "IDA* Solved successfully!" << endl;
  } else {
    cout << "IDA* Failed to solve." << endl;
  }

  return 0;
}