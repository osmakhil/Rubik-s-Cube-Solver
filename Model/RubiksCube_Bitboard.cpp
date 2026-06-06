#include "RubiksCube_Bitboard.hpp"

/*
===============================================================================
RUBIK'S CUBE BITBOARD REPRESENTATION
===============================================================================

Instead of storing 54 stickers separately, we store the cube as:

    uint64_t bitboard[6];

Each element represents ONE FACE of the cube.

    bitboard[0] -> Up (White)
    bitboard[1] -> Left (Green)
    bitboard[2] -> Front (Red)
    bitboard[3] -> Right (Blue)
    bitboard[4] -> Back (Orange)
    bitboard[5] -> Down (Yellow)

-------------------------------------------------------------------------------
COLOR ENCODING
-------------------------------------------------------------------------------

Each sticker color is stored in 8 bits (1 byte).

Only ONE bit is set for each color.

    White   = 00000001   (1 << 0)
    Green   = 00000010   (1 << 1)
    Red     = 00000100   (1 << 2)
    Blue    = 00001000   (1 << 3)
    Orange  = 00010000   (1 << 4)
    Yellow  = 00100000   (1 << 5)

This makes extracting and comparing colors very fast.

-------------------------------------------------------------------------------
FACE REPRESENTATION
-------------------------------------------------------------------------------

A face contains 9 stickers.

The center sticker NEVER moves, therefore we store only the remaining 8
stickers.

Each sticker occupies 8 bits.

    8 stickers × 8 bits = 64 bits

Therefore ONE FACE fits exactly inside ONE uint64_t.

-------------------------------------------------------------------------------
STICKER INDEXING
-------------------------------------------------------------------------------

The 8 movable stickers are indexed clockwise:

         0   1   2

         7   C   3

         6   5   4

(C = center sticker, not stored)

Clockwise ordering is chosen because rotating a face becomes extremely simple.

-------------------------------------------------------------------------------
BIT LAYOUT INSIDE uint64_t
-------------------------------------------------------------------------------

Index 0 occupies bits 0-7.
Index 1 occupies bits 8-15.
Index 2 occupies bits 16-23.
...
Index 7 occupies bits 56-63.

Visual layout:

    | idx7 | idx6 | idx5 | idx4 | idx3 | idx2 | idx1 | idx0 |
      63                                                 ... 0

Example:

    Sticker colors:

         W   G   R
         G   C   B
         W   Y   O

    Clockwise sequence:

         W G R B O Y W G
         0 1 2 3 4 5 6 7

Stored as:

         [G][W][Y][O][B][R][G][W]

(Most significant byte on left)

-------------------------------------------------------------------------------
WHY CLOCKWISE INDEXING?
-------------------------------------------------------------------------------

A clockwise face rotation simply moves every sticker forward by 2 positions:

Before:

         0 1 2
         7 C 3
         6 5 4

After clockwise rotation:

         6 7 0
         5 C 1
         4 3 2

Equivalent sequence change:

         0 1 2 3 4 5 6 7
           ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓
         6 7 0 1 2 3 4 5

This is exactly a circular shift by 2 sticker positions.

Since each sticker occupies 8 bits:

         2 positions × 8 bits = 16 bits

Therefore rotating a face clockwise can be implemented as:

         rotate_left(face, 16)

or

         (face << 16) | (face >> 48)

This updates all 8 stickers of the face in O(1).

-------------------------------------------------------------------------------
FACE ROTATION LOGIC
-------------------------------------------------------------------------------

A move consists of TWO parts:

1. Rotate the face itself
       -> rotate the 64-bit integer by 16 bits

2. Update adjacent faces
       -> manually exchange edge stickers between
          neighbouring faces

Example: F move

       Up    -> Right
       Right -> Down
       Down  -> Left
       Left  -> Up

The face rotation is automatic via bit rotation.
The neighbouring edge transfers must still be coded manually.

-------------------------------------------------------------------------------
ADVANTAGES
-------------------------------------------------------------------------------

✓ Extremely compact (6 × 8 bytes = 48 bytes)
✓ Fast hashing
✓ Fast comparisons
✓ O(1) face rotations
✓ Excellent for BFS/IDA/Pattern Database solvers

===============================================================================
*/

void RubiksCubeBitboard::rotateFace(int ind) {
  uint64_t side = bitboard[ind];
  side = side >> (8 * 6);
  bitboard[ind] = (bitboard[ind] << (8 * 2)) | (side);
}

void RubiksCubeBitboard::rotateSide(int dstFace, int dst1, int dst2, int dst3, int srcFace,
                                    int src1, int src2, int src3) {

  uint64_t clr1 = (bitboard[srcFace] & (one_8 << (8 * src1))) >> (8 * src1);
  uint64_t clr2 = (bitboard[srcFace] & (one_8 << (8 * src2))) >> (8 * src2);
  uint64_t clr3 = (bitboard[srcFace] & (one_8 << (8 * src3))) >> (8 * src3);

  bitboard[dstFace] =
      (bitboard[dstFace] & ~(one_8 << (8 * dst1))) | (clr1 << (8 * dst1));
  bitboard[dstFace] =
      (bitboard[dstFace] & ~(one_8 << (8 * dst2))) | (clr2 << (8 * dst2));
  bitboard[dstFace] =
      (bitboard[dstFace] & ~(one_8 << (8 * dst3))) | (clr3 << (8 * dst3));
}

int RubiksCubeBitboard::get5bitCorner(string corner) {
  int ret = 0;
  string actual_str;
  for (auto c : corner) {
    if (c != 'W' && c != 'Y')
      continue;
    actual_str.push_back(c);
    if (c == 'Y') {
      ret |= (1 << 2);
    }
  }

  for (auto c : corner) {
    if (c != 'R' && c != 'O')
      continue;
    if (c == 'O') {
      ret |= (1 << 1);
    }
  }

  for (auto c : corner) {
    if (c != 'B' && c != 'G')
      continue;
    if (c == 'G') {
      ret |= (1 << 0);
    }
  }

  if (corner[1] == actual_str[0]) {
    ret |= (1 << 3);
  } else if (corner[2] == actual_str[0]) {
    ret |= (1 << 4);
  }
  return ret;
}

RubiksCubeBitboard::RubiksCubeBitboard() {
  for (int side = 0; side < 6; side++) {
    uint64_t clr = 1 << side;
    bitboard[side] = 0;
    for (int faceIdx = 0; faceIdx < 8; faceIdx++) {
      bitboard[side] |= clr << (8 * faceIdx);
    }
    solved_side_config[side] = bitboard[side];
  }
}

RubiksCube::COLOR RubiksCubeBitboard::getColor(FACE face, unsigned row, unsigned col) const {
  int idx = arr[row][col];
  if (idx == 8)
    return (COLOR)((int)face);

  uint64_t side = bitboard[(int)face];
  uint64_t color = (side >> (8 * idx)) & one_8;

  int bit_pos = 0;
  while (color != 0) {
    color = color >> 1;
    bit_pos++;
  }
  return (COLOR)(bit_pos - 1);
}

bool RubiksCubeBitboard::isSolved() const {
  for (int i = 0; i < 6; i++) {
    if (solved_side_config[i] != bitboard[i])
      return false;
  }
  return true;
}

RubiksCube &RubiksCubeBitboard::u() {
  this->rotateFace(0);
  uint64_t temp = bitboard[2] & one_24;
  bitboard[2] = (bitboard[2] & ~one_24) | (bitboard[3] & one_24);
  bitboard[3] = (bitboard[3] & ~one_24) | (bitboard[4] & one_24);
  bitboard[4] = (bitboard[4] & ~one_24) | (bitboard[1] & one_24);
  bitboard[1] = (bitboard[1] & ~one_24) | temp;

  return *this;
}

RubiksCube &RubiksCubeBitboard::uPrime() {
  this->u();
  this->u();
  this->u();

  return *this;
}

RubiksCube &RubiksCubeBitboard::u2() {
  this->u();
  this->u();

  return *this;
}

RubiksCube &RubiksCubeBitboard::l() {
  this->rotateFace(1);
  uint64_t clr1 = (bitboard[2] & (one_8 << (8 * 0))) >> (8 * 0);
  uint64_t clr2 = (bitboard[2] & (one_8 << (8 * 6))) >> (8 * 6);
  uint64_t clr3 = (bitboard[2] & (one_8 << (8 * 7))) >> (8 * 7);

  this->rotateSide(2, 0, 7, 6, 0, 0, 7, 6);
  this->rotateSide(0, 0, 7, 6, 4, 4, 3, 2);
  this->rotateSide(4, 4, 3, 2, 5, 0, 7, 6);

  bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 0))) | (clr1 << (8 * 0));
  bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 6))) | (clr2 << (8 * 6));
  bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 7))) | (clr3 << (8 * 7));

  return *this;
}

RubiksCube &RubiksCubeBitboard::lPrime() {
  this->l();
  this->l();
  this->l();

  return *this;
}

RubiksCube &RubiksCubeBitboard::l2() {
  this->l();
  this->l();

  return *this;
}

RubiksCube &RubiksCubeBitboard::f() {
  this->rotateFace(2);

  uint64_t clr1 = (bitboard[0] & (one_8 << (8 * 4))) >> (8 * 4);
  uint64_t clr2 = (bitboard[0] & (one_8 << (8 * 5))) >> (8 * 5);
  uint64_t clr3 = (bitboard[0] & (one_8 << (8 * 6))) >> (8 * 6);

  this->rotateSide(0, 4, 5, 6, 1, 2, 3, 4);
  this->rotateSide(1, 2, 3, 4, 5, 0, 1, 2);
  this->rotateSide(5, 0, 1, 2, 3, 6, 7, 0);

  bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
  bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
  bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));

  return *this;
}

RubiksCube &RubiksCubeBitboard::fPrime() {
  this->f();
  this->f();
  this->f();
  return *this;
}

RubiksCube &RubiksCubeBitboard::f2() {
  this->f();
  this->f();

  return *this;
}

RubiksCube &RubiksCubeBitboard::r() {
  this->rotateFace(3);
  uint64_t clr1 = (bitboard[0] & (one_8 << (8 * 2))) >> (8 * 2);
  uint64_t clr2 = (bitboard[0] & (one_8 << (8 * 3))) >> (8 * 3);
  uint64_t clr3 = (bitboard[0] & (one_8 << (8 * 4))) >> (8 * 4);

  this->rotateSide(0, 2, 3, 4, 2, 2, 3, 4);
  this->rotateSide(2, 2, 3, 4, 5, 2, 3, 4);
  this->rotateSide(5, 2, 3, 4, 4, 7, 6, 0);

  bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 7))) | (clr1 << (8 * 7));
  bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 6))) | (clr2 << (8 * 6));
  bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));

  return *this;
}

RubiksCube &RubiksCubeBitboard::rPrime() {
  this->r();
  this->r();
  this->r();

  return *this;
}

RubiksCube &RubiksCubeBitboard::r2() {
  this->r();
  this->r();

  return *this;
}

RubiksCube &RubiksCubeBitboard::b() {
  this->rotateFace(4);

  uint64_t clr1 = (bitboard[0] & (one_8 << (8 * 0))) >> (8 * 0);
  uint64_t clr2 = (bitboard[0] & (one_8 << (8 * 1))) >> (8 * 1);
  uint64_t clr3 = (bitboard[0] & (one_8 << (8 * 2))) >> (8 * 2);

  this->rotateSide(0, 0, 1, 2, 3, 2, 3, 4);
  this->rotateSide(3, 2, 3, 4, 5, 4, 5, 6);
  this->rotateSide(5, 4, 5, 6, 1, 6, 7, 0);

  bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
  bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
  bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));

  return *this;
}

RubiksCube &RubiksCubeBitboard::bPrime() {
  this->b();
  this->b();
  this->b();

  return *this;
}

RubiksCube &RubiksCubeBitboard::b2() {
  this->b();
  this->b();

  return *this;
}

RubiksCube &RubiksCubeBitboard::d() {
  this->rotateFace(5);

  uint64_t clr1 = (bitboard[2] & (one_8 << (8 * 4))) >> (8 * 4);
  uint64_t clr2 = (bitboard[2] & (one_8 << (8 * 5))) >> (8 * 5);
  uint64_t clr3 = (bitboard[2] & (one_8 << (8 * 6))) >> (8 * 6);

  this->rotateSide(2, 4, 5, 6, 1, 4, 5, 6);
  this->rotateSide(1, 4, 5, 6, 4, 4, 5, 6);
  this->rotateSide(4, 4, 5, 6, 3, 4, 5, 6);

  bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 4))) | (clr1 << (8 * 4));
  bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 5))) | (clr2 << (8 * 5));
  bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 6))) | (clr3 << (8 * 6));

  return *this;
}

RubiksCube &RubiksCubeBitboard::dPrime() {
  this->d();
  this->d();
  this->d();

  return *this;
}

RubiksCube &RubiksCubeBitboard::d2() {
  this->d();
  this->d();

  return *this;
}

bool RubiksCubeBitboard::operator==(const RubiksCubeBitboard &r1) const {
  for (int i = 0; i < 6; i++) {
    if (bitboard[i] != r1.bitboard[i])
      return false;
  }
  return true;
}

RubiksCubeBitboard &RubiksCubeBitboard::operator=(const RubiksCubeBitboard &r1) {
  for (int i = 0; i < 6; i++) {
    bitboard[i] = r1.bitboard[i];
  }
  return *this;
}

uint64_t RubiksCubeBitboard::getCorners() {
  uint64_t ret = 0;
  string top_front_right = "";
  top_front_right += getColorLetter(getColor(FACE::UP, 2, 2));
  top_front_right += getColorLetter(getColor(FACE::FRONT, 0, 2));
  top_front_right += getColorLetter(getColor(FACE::RIGHT, 0, 0));

  string top_front_left = "";
  top_front_left += getColorLetter(getColor(FACE::UP, 2, 0));
  top_front_left += getColorLetter(getColor(FACE::FRONT, 0, 0));
  top_front_left += getColorLetter(getColor(FACE::LEFT, 0, 2));

  string top_back_left = "";
  top_back_left += getColorLetter(getColor(FACE::UP, 0, 0));
  top_back_left += getColorLetter(getColor(FACE::BACK, 0, 2));
  top_back_left += getColorLetter(getColor(FACE::LEFT, 0, 0));

  string top_back_right = "";
  top_back_right += getColorLetter(getColor(FACE::UP, 0, 2));
  top_back_right += getColorLetter(getColor(FACE::BACK, 0, 0));
  top_back_right += getColorLetter(getColor(FACE::RIGHT, 0, 2));

  string bottom_front_right = "";
  bottom_front_right += getColorLetter(getColor(FACE::DOWN, 0, 2));
  bottom_front_right += getColorLetter(getColor(FACE::FRONT, 2, 2));
  bottom_front_right += getColorLetter(getColor(FACE::RIGHT, 2, 0));

  string bottom_front_left = "";
  bottom_front_left += getColorLetter(getColor(FACE::DOWN, 0, 0));
  bottom_front_left += getColorLetter(getColor(FACE::FRONT, 2, 0));
  bottom_front_left += getColorLetter(getColor(FACE::LEFT, 2, 2));

  string bottom_back_right = "";
  bottom_back_right += getColorLetter(getColor(FACE::DOWN, 2, 2));
  bottom_back_right += getColorLetter(getColor(FACE::BACK, 2, 0));
  bottom_back_right += getColorLetter(getColor(FACE::RIGHT, 2, 2));

  string bottom_back_left = "";
  bottom_back_left += getColorLetter(getColor(FACE::DOWN, 2, 0));
  bottom_back_left += getColorLetter(getColor(FACE::BACK, 2, 2));
  bottom_back_left += getColorLetter(getColor(FACE::LEFT, 2, 0));

  ret |= get5bitCorner(top_front_right);
  ret = ret << 5;

  ret |= get5bitCorner(top_front_left);
  ret = ret << 5;

  ret |= get5bitCorner(top_back_right);
  ret = ret << 5;

  ret |= get5bitCorner(top_back_left);
  ret = ret << 5;

  ret |= get5bitCorner(bottom_front_right);
  ret = ret << 5;

  ret |= get5bitCorner(bottom_front_left);
  ret = ret << 5;

  ret |= get5bitCorner(bottom_back_right);
  ret = ret << 5;

  ret |= get5bitCorner(bottom_back_left);
  ret = ret << 5;

  return ret;
}

size_t HashBitboard::operator()(const RubiksCubeBitboard &r1) const {
  uint64_t final_hash = r1.bitboard[0];
  for (int i = 1; i < 6; i++)
    final_hash ^= r1.bitboard[i];
  return (size_t)final_hash;
}