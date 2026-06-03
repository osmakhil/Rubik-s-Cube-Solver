#include "RubiksCube.hpp"
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

// Face stickers are stored clockwise.
// One sticker = 8 bits.
// Clockwise face rotation = circular shift by 2 stickers = 16 bits.

class RubiksCubeBitboard : public RubiksCube {

private:
  uint64_t solved_side_config[6]{};
  uint64_t one_8 = (1 << 8) - 1;

  void rotateFace(int ind) {
    uint64_t side = bitboard[ind];
    side = side >> (8 * 6);
    bitboard[ind] = (bitboard[ind] << (8 * 2)) | (side);
  }

  // Copies 3 sticker positions from one face to another.
  void rotateSide(int dstFace, int dst1, int dst2, int dst3, int srcFace,
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

public:
  uint64_t bitboard[6]{};
};