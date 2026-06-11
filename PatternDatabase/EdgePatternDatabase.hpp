#ifndef RUBIKS_CUBE_SOLVER_EDGEPATTERNDATABASE_H
#define RUBIKS_CUBE_SOLVER_EDGEPATTERNDATABASE_H

#include "../Model/RubiksCube.hpp"
#include "PatternDatabase.hpp"
#include "PermutationIndexer.hpp"
using namespace std;

class EdgePatternDatabase : public PatternDatabase
{

    PermutationIndexer<12, 6> permIndexer;

    // Which 6 edge positions this DB tracks
    array<uint8_t, 6> trackedEdges;

public:
    EdgePatternDatabase(array<uint8_t, 6> edges);
    EdgePatternDatabase(array<uint8_t, 6> edges, uint8_t init_val);
    uint32_t getDatabaseIndex(const RubiksCube &cube) const;
};
#endif