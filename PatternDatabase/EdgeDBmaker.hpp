
#ifndef RUBIKS_CUBE_SOLVER_EDGEDBMAKER_H
#define RUBIKS_CUBE_SOLVER_EDGEDBMAKER_H
#include "../Model/RubiksCube_Bitboard.hpp"
#include "EdgePatternDatabase.hpp"
#include <string>
#include <array>

using namespace std;

class EdgeDBmaker
{
private:
    string fileName;
    EdgePatternDatabase edgeDB;

public:
    EdgeDBmaker(string _fileName, array<uint8_t, 6> edges);
    EdgeDBmaker(string _fileName, array<uint8_t, 6> edges, uint8_t init_val);

    bool bfsAndStore();
};

#endif