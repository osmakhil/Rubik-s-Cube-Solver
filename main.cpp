#include "Model/RubiksCube_3DArray.cpp"
#include <iostream>

using namespace std;

int main() {

  RubiksCube3dArray cube;

  auto moves = cube.randomShuffleCube(3);
  for (auto mov : moves) {
    cout << cube.getMove(mov) << " ";
  }

  cube.print();
}