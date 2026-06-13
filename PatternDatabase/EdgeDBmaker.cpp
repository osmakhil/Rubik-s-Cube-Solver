#include "EdgeDBmaker.hpp"
#include <iostream>
#include <vector>

EdgeDBmaker::EdgeDBmaker(string _fileName, array<uint8_t, 6> _edges)
    : fileName(_fileName), edgeDB(_edges) {};

EdgeDBmaker::EdgeDBmaker(string _fileName, array<uint8_t, 6> _edges,
                         uint8_t _init_val)
    : fileName(_fileName), edgeDB(_edges, _init_val) {};

bool EdgeDBmaker::bfsAndStore() {

  if (edgeDB.fromFile(fileName)) {
    cout << "Loaded EdgeDB from file " << fileName << "\n";
    return true;
  }

  RubiksCubeBitboard solvedCube;
  edgeDB.setNumMoves(solvedCube, 0);

  // Store cube + last move used to reach it
  // lastMove = -1 means no previous move (start state)
  vector<pair<RubiksCubeBitboard, int8_t>> currentLevel, nextLevel;
  currentLevel.push_back({solvedCube, -1});

  // Moves grouped by face:
  // L=0,L'=1,L2=2 | R=3,R'=4,R2=5 | U=6,U'=7,U2=8
  // D=9,D'=10,D2=11 | F=12,F'=13,F2=14 | B=15,B'=16,B2=17
  // move/3 gives face group → same face group = redundant move

  uint8_t targetDepth = 10;
  for (uint8_t depth = 0; depth < targetDepth && !edgeDB.isFull(); ++depth) {
    cout << "Depth " << (int)depth << " | Frontier: " << currentLevel.size()
         << " | DB filled: " << edgeDB.getNumItems() << " / "
         << edgeDB.getSize() << "\n";
    cout.flush();

    nextLevel.clear();
    nextLevel.reserve(currentLevel.size() * 13); // ~13 moves after pruning

    for (auto &[cube, lastMove] : currentLevel) {
      for (int i = 0; i < 18; i++) {
        // Pruning: skip if same face group as last move
        // e.g. skip R' or R2 if last move was R
        if (lastMove != -1 && (i / 3 == lastMove / 3))
          continue;

        RubiksCubeBitboard next = cube;
        next.move(RubiksCube::MOVE(i));

        if (edgeDB.setNumMoves(next, depth + 1))
          nextLevel.push_back({next, i});
      }
    }

    currentLevel.clear();
    currentLevel.shrink_to_fit();
    swap(currentLevel, nextLevel);
  }

  if (!edgeDB.isFull())
    cout << "WARNING: DB not full after max depth!\n";
  else
    cout << "BFS complete. DB items: " << edgeDB.getNumItems() << "\n";

  edgeDB.toFile(fileName);
  cout << "Saved to: " << fileName << "\n";
  return edgeDB.isFull();
}