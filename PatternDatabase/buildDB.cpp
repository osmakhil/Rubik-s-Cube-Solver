#include "CornerDBmaker.hpp"
#include "EdgeDBmaker.hpp"
#include <iostream>

using namespace std;

int main() {
  string filePath = "PatternDatabase/cornerDepth8.dat";
  cout << "Creating Corner Pattern Database at: " << filePath << "..." << endl;

  // Initialize CornerDBmaker with the target file path and initial value 0xFF
  CornerDBmaker dbMaker(filePath, 0xFF);

  // Run BFS and save database to file
  dbMaker.bfsAndStore();

  cout << "Corner Pattern Database created successfully!" << endl;

  // 2. Create Edge Database 1 (UF, UB, FR, BL, DF, DB)
  string edgeFilePath1 = "PatternDatabase/edgeDepth10_1.dat";
  cout << "Creating Edge Pattern Database 1 at: " << edgeFilePath1 << "..."
       << endl;
  array<uint8_t, 6> edges1 = {0, 2, 4, 7, 8, 10};
  EdgeDBmaker edgeMaker1(edgeFilePath1, edges1, 0xFF);
  edgeMaker1.bfsAndStore();
  cout << "Edge Pattern Database 1 created successfully!\n" << endl;

  // 3. Create Edge Database 2 (UR, UL, FL, BR, DR, DL)
  string edgeFilePath2 = "PatternDatabase/edgeDepth10_2.dat";
  cout << "Creating Edge Pattern Database 2 at: " << edgeFilePath2 << "..."
       << endl;
  array<uint8_t, 6> edges2 = {1, 3, 5, 6, 9, 11};
  EdgeDBmaker edgeMaker2(edgeFilePath2, edges2, 0xFF);
  edgeMaker2.bfsAndStore();
  cout << "Edge Pattern Database 2 created successfully!\n" << endl;

  return 0;

  return 0;
}
