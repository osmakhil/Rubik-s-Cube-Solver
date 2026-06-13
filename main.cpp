#include "Model/RubiksCube_3DArray.hpp"
#include "Model/RubiksCube_Bitboard.hpp"
// #include "Solver/BFSSolver.hpp"
// #include "Solver/DFSSolver.hpp"
#include "Solver/IDAStarSolver.hpp"
// #include "Solver/IDDFSSolver.hpp"
#include <iostream>

using namespace std;

int main() {
  RubiksCubeBitboard cube;

  // // 1. IDDFS Solver
  // // cout << "\n[IDDFS Solving]\n";
  // // RubiksCubeBitboard cubeIDDFS = cube;
  // // IDDFSSolver<RubiksCubeBitboard, HashBitboard> iddfsSolver(cubeIDDFS, 7);
  // // auto iddfsSolution = iddfsSolver.solve();
  // // cout << "IDDFS Moves found (" << iddfsSolution.size() << "): ";
  // // for (auto m : iddfsSolution)
  // //   cout << cubeIDDFS.getMove(m) << " ";
  // // cout << "\n";

  // // // Apply the moves to the copy to verify it solves the cube
  // // for (auto m : iddfsSolution)
  // //   cubeIDDFS.move(m);

  // // if (cubeIDDFS.isSolved()) {
  // //   cout << "IDDFS Solved successfully!" << endl;
  // // } else {
  // //   cout << "IDDFS Failed to solve." << endl;
  // // }

  // 2. IDA* Solver (using the precomputed pattern databases)
  cout << "\n[IDA* Solving]\n";
  RubiksCubeBitboard cubeIDAStar = cube;

  // Perform a few random moves to shuffle the cube so we have something to
  // solve
  vector<RubiksCube::MOVE> shuffleMoves = cubeIDAStar.randomShuffleCube(20);
  cout << "Shuffled cube with moves: ";
  for (auto m : shuffleMoves)
    cout << cubeIDAStar.getMove(m) << " ";
  cout << "\n";

  IDAstarSolver<RubiksCubeBitboard, HashBitboard> idastarSolver(
      cubeIDAStar, "PatternDatabase/cornerDepth8.dat",
      "PatternDatabase/edgeDepth10_1.dat", "PatternDatabase/edgeDepth10_2.dat");

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