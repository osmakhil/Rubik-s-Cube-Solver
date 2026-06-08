#include <iostream>
#include "PatternDatabase/CornerDBmaker.hpp"

using namespace std;

int main() {
    string filePath = "PatternDatabase/cornerDepth8.dat";
    cout << "Creating Corner Pattern Database at: " << filePath << "..." << endl;
    cout << "This might take a minute..." << endl;

    // Initialize CornerDBmaker with the target file path and initial value 0xFF
    CornerDBmaker dbMaker(filePath, 0xFF);
    
    // Run BFS and save database to file
    dbMaker.bfsAndStore();

    cout << "Corner Pattern Database created successfully!" << endl;

    return 0;
}
