#include "EdgePatternDatabase.hpp"

EdgePatternDatabase::EdgePatternDatabase(array<uint8_t, 6> edges)
    : PatternDatabase(42577920), trackedEdges(edges) {};

EdgePatternDatabase::EdgePatternDatabase(array<uint8_t, 6> edges, uint8_t init_val)
    : PatternDatabase(42577920, init_val), trackedEdges(edges) {}

uint32_t EdgePatternDatabase::getDatabaseIndex(const RubiksCube &cube) const
{

    // Which cubie is sitting in the slot
    array<uint8_t, 6> edgePerm;
    for (int i = 0; i < 6; i++)
        edgePerm[i] = cube.getEdgeIndex(trackedEdges[i]);

    // Rank the partial permutation -> 0 to P(12,6)-1
    uint32_t rank = permIndexer.rank(edgePerm);

    // orientation of each edge
    uint32_t orientNum = 0;
    for (int i = 0; i < 6; i++)
        orientNum = (orientNum << 1) | cube.getEdgeOrientation(trackedEdges[i]);

    return rank * 64 + orientNum;
}