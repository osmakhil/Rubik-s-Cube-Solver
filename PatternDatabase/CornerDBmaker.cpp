#include "CornerDBmaker.hpp"
#include <iostream>
#include <vector>

using namespace std;

CornerDBmaker::CornerDBmaker(string _fileName) : fileName(_fileName) {}

CornerDBmaker::CornerDBmaker(string _fileName, uint8_t init_val)
    : fileName(_fileName), cornerDB(init_val) {}

bool CornerDBmaker::bfsAndStore()
{
  // Load from file if already built
  if (cornerDB.fromFile(fileName))
  {
    cout << "Loaded corner DB from file: " << fileName << "\n";
    return true;
  }

  RubiksCubeBitboard solvedCube;
  cornerDB.setNumMoves(solvedCube, 0);

  // KEY CHANGE: frontier only holds current + next level
  // NOT a queue of full cube objects across all depths
  vector<RubiksCubeBitboard> currentLevel, nextLevel;
  currentLevel.push_back(solvedCube);

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
    nextLevel.reserve(currentLevel.size() * 6);

    for (auto &cube : currentLevel)
    {
      for (int i = 0; i < 18; i++)
      {
        auto move = RubiksCube::MOVE(i);

        RubiksCubeBitboard next = cube; // copy
        next.move(move);

        // setNumMoves returns true only if this is a NEW state
        // (0xFF unvisited) — no duplicates pushed
        if (cornerDB.setNumMoves(next, depth + 1))
        {
          nextLevel.push_back(next);
        }
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