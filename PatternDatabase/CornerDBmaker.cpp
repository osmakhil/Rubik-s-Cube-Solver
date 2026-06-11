#include "CornerDBmaker.hpp"
#include <iostream>
#include <vector>

using namespace std;

CornerDBmaker::CornerDBmaker(string _fileName) : fileName(_fileName) {}

CornerDBmaker::CornerDBmaker(string _fileName, uint8_t init_val)
    : fileName(_fileName), cornerDB(init_val) {}

bool CornerDBmaker::bfsAndStore()
{
  if (cornerDB.fromFile(fileName))
  {
    cout << "Loaded corner DB from file: " << fileName << "\n";
    return true;
  }

  RubiksCubeBitboard solvedCube;
  cornerDB.setNumMoves(solvedCube, 0);

  vector<pair<RubiksCubeBitboard, int8_t>> currentLevel, nextLevel;
  currentLevel.push_back({solvedCube, -1});

  uint8_t targetDepth = 11;

  for (uint8_t depth = 0; depth < targetDepth; ++depth)
  {
    cout << "Depth " << (int)depth
         << " | Frontier: " << currentLevel.size()
         << " | DB filled: " << cornerDB.getNumItems()
         << " / " << cornerDB.getSize() << "\n";
    cout.flush();

    // Reserve to avoid repeated heap reallocations
    nextLevel.clear();
    nextLevel.reserve(currentLevel.size() * 13);

    for (auto &[cube, lastMove] : currentLevel)
    {
      for (int i = 0; i < 18; i++)
      {
        // Pruning: skip if same face group as last move
        if (lastMove != -1 && (i / 3 == lastMove / 3))
          continue;

        RubiksCubeBitboard next = cube;
        next.move(RubiksCube::MOVE(i));

        if (cornerDB.setNumMoves(next, depth + 1))
          nextLevel.push_back({next, i});
      }
    }

    // Free current level memory before swap
    currentLevel.clear();
    currentLevel.shrink_to_fit();
    swap(currentLevel, nextLevel);

    if (cornerDB.isFull())
      break;
  }

  cout << "BFS complete. DB items: " << cornerDB.getNumItems() << "\n";
  cornerDB.toFile(fileName);
  cout << "Saved to: " << fileName << "\n";
  return cornerDB.isFull();
}