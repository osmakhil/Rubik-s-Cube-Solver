#ifndef RUBIKS_CUBE_SOLVER_RUBIKSCUBE_BITBOARD_H
#define RUBIKS_CUBE_SOLVER_RUBIKSCUBE_BITBOARD_H

#include "RubiksCube.hpp"

class RubiksCubeBitboard : public RubiksCube {

private:
  uint64_t solved_side_config[6]{};

  int arr[3][3] = {{0, 1, 2}, {7, 8, 3}, {6, 5, 4}};

  uint64_t one_8 = (1 << 8) - 1;
  uint64_t one_24 = (1 << 24) - 1;

  void rotateFace(int ind);

  // Copies 3 sticker positions from srcFace to dstFace.
  void rotateSide(int dstFace, int dst1, int dst2, int dst3, int srcFace,
                  int src1, int src2, int src3);

  // Encodes a corner cubie into 5 bits.
  int get5bitCorner(string corner);

public:
  uint64_t bitboard[6]{};

  RubiksCubeBitboard();

  COLOR getColor(FACE face, unsigned row, unsigned col) const override;

  bool isSolved() const override;

  RubiksCube &u() override;

  RubiksCube &uPrime() override;

  RubiksCube &u2() override;

  RubiksCube &l() override;

  RubiksCube &lPrime() override;

  RubiksCube &l2() override;

  RubiksCube &f() override;

  RubiksCube &fPrime() override;

  RubiksCube &f2() override;

  RubiksCube &r() override;

  RubiksCube &rPrime() override;

  RubiksCube &r2() override;

  RubiksCube &b() override;

  RubiksCube &bPrime() override;

  RubiksCube &b2() override;

  RubiksCube &d() override;

  RubiksCube &dPrime() override;

  RubiksCube &d2() override;

  bool operator==(const RubiksCubeBitboard &r1) const;

  RubiksCubeBitboard &operator=(const RubiksCubeBitboard &r1);

  uint64_t getCorners();
};

struct HashBitboard {
  size_t operator()(const RubiksCubeBitboard &r1) const;
};

#endif // RUBIKS_CUBE_SOLVER_RUBIKSCUBE_BITBOARD_H
