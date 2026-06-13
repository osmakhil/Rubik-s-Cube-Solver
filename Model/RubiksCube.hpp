#pragma once
#include <iostream>
#include <vector>
using namespace std;

/*
A base class for all Rubik's cube model. There are varios representation of
Rubik's cube Each one has it's own functionality and definitions. This class
shared common functionality between models
*/

class RubiksCube {

public:
  enum class FACE { UP, LEFT, FRONT, RIGHT, BACK, DOWN };
  enum class COLOR { WHITE, GREEN, RED, BLUE, ORANGE, YELLOW };
  enum class MOVE {
    L,
    LPRIME,
    L2,
    R,
    RPRIME,
    R2,
    U,
    UPRIME,
    U2,
    D,
    DPRIME,
    D2,
    F,
    FPRIME,
    F2,
    B,
    BPRIME,
    B2
  };

  /*
   * Returns the color of the cell at (row, col) in face.
   * If Rubik's Cube face is pointing at you, then the row numbering starts from
   * the top to bottom, and column numbering starts from the left to right. The
   * rows and columns are 0-indexed.
   * @param Face, row, and column index
   */
  virtual COLOR getColor(FACE face, unsigned row, unsigned col) const = 0;

  /*
   * Returns the first letter of the given COLOR
   * Eg: For COLOR::GREEN, it returns 'G'
   */
  static char getColorLetter(COLOR color);

  /*
  Retrun true if the cube is solved
  */
  virtual bool isSolved() const = 0;

  /*
   * Returns the move in the string format.
   */
  static string getMove(MOVE ind);

  /*
   * Print the Rubik Cube in Planar format.
   *
   * The cube is laid out as follows.
   *
   * The sides:
   *    U
   *  L F R B
   *    D
   *
   * Color wise:
   *
   *          W W W
   *          W W W
   *          W W W
   *
   *  G G G   R R R   B B B   O O O
   *  G G G   R R R   B B B   O O O
   *  G G G   R R R   B B B   O O O
   *
   *          Y Y Y
   *          Y Y Y
   *          Y Y Y
   *
   * Row and Column Numberings:
   * rx -> row numbering
   * cx -> column numbering
   * bx -> both row and column numbering
   *
   *             b0 c1 c2
   *             r1  .  .
   *             r2  .  .
   *
   *  b0 c1 c2   b0 c1 c2   b0 c1 c2   b0 c1 c2
   *  r1  .  .   r1  .  .   r1  .  .   r1  .  .
   *  r2  .  .   r2  .  .   r2  .  .   r2  .  .
   *
   *             b0 c1 c2
   *             r1  .  .
   *             r2  .  .
   *
   */
  void print() const;

  /*
   * Randomly shuffle the cube with 'times' moves and returns the moves
   * performed.
   */
  vector<MOVE> randomShuffleCube(unsigned int times);

  /*
  Performs move on the Rubik's cube
  */
  RubiksCube &move(MOVE ind);

  /*
   * Invert a move
   */
  RubiksCube &invert(MOVE ind);

  virtual RubiksCube &f() = 0;

  virtual RubiksCube &fPrime() = 0;

  virtual RubiksCube &f2() = 0;

  virtual RubiksCube &u() = 0;

  virtual RubiksCube &uPrime() = 0;

  virtual RubiksCube &u2() = 0;

  virtual RubiksCube &l() = 0;

  virtual RubiksCube &lPrime() = 0;

  virtual RubiksCube &l2() = 0;

  virtual RubiksCube &r() = 0;

  virtual RubiksCube &d() = 0;

  virtual RubiksCube &dPrime() = 0;

  virtual RubiksCube &d2() = 0;

  virtual RubiksCube &rPrime() = 0;

  virtual RubiksCube &r2() = 0;

  virtual RubiksCube &b() = 0;

  virtual RubiksCube &bPrime() = 0;

  virtual RubiksCube &b2() = 0;

  string getCornerColorString(uint8_t ind) const;

  void getCornerColors(uint8_t ind, COLOR &c_ud, COLOR &c_fb,
                       COLOR &c_lr) const;

  uint8_t getCornerIndex(uint8_t ind) const;

  uint8_t getCornerOrientation(uint8_t ind) const;

  string getEdgeColorString(uint8_t ind) const;

  uint8_t getEdgeIndex(uint8_t ind) const;

  uint8_t getEdgeOrientation(uint8_t ind) const;

  virtual ~RubiksCube() {}
};