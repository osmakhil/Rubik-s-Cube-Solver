#include "RubiksCube.hpp"

//
// Given a color return it's first letter
//

char RubiksCube::getColorLetter(COLOR color) {
  switch (color) {
  case COLOR::BLUE:
    return 'B';
  case COLOR::GREEN:
    return 'G';
  case COLOR::RED:
    return 'R';
  case COLOR::YELLOW:
    return 'Y';
  case COLOR::WHITE:
    return 'W';
  case COLOR::ORANGE:
    return 'O';
  }
}

/*
 * Describe a move using an index
 */
string RubiksCube::getMove(MOVE ind) {
  switch (ind) {
  case MOVE::L:
    return "L";
  case MOVE::LPRIME:
    return "L'";
  case MOVE::L2:
    return "L2";
  case MOVE::R:
    return "R";
  case MOVE::RPRIME:
    return "R'";
  case MOVE::R2:
    return "R2";
  case MOVE::U:
    return "U";
  case MOVE::UPRIME:
    return "U'";
  case MOVE::U2:
    return "U2";
  case MOVE::D:
    return "D";
  case MOVE::DPRIME:
    return "D'";
  case MOVE::D2:
    return "D2";
  case MOVE::F:
    return "F";
  case MOVE::FPRIME:
    return "F'";
  case MOVE::F2:
    return "F2";
  case MOVE::B:
    return "B";
  case MOVE::BPRIME:
    return "B'";
  case MOVE::B2:
    return "B2";
  }
}

/*
 * Perform a move operation on using a Move index.
 */
RubiksCube &RubiksCube::move(MOVE ind) {
  switch (ind) {
  case MOVE::L:
    return this->l();
  case MOVE::LPRIME:
    return this->lPrime();
  case MOVE::L2:
    return this->l2();
  case MOVE::R:
    return this->r();
  case MOVE::RPRIME:
    return this->rPrime();
  case MOVE::R2:
    return this->r2();
  case MOVE::U:
    return this->u();
  case MOVE::UPRIME:
    return this->uPrime();
  case MOVE::U2:
    return this->u2();
  case MOVE::D:
    return this->d();
  case MOVE::DPRIME:
    return this->dPrime();
  case MOVE::D2:
    return this->d2();
  case MOVE::F:
    return this->f();
  case MOVE::FPRIME:
    return this->fPrime();
  case MOVE::F2:
    return this->f2();
  case MOVE::B:
    return this->b();
  case MOVE::BPRIME:
    return this->bPrime();
  case MOVE::B2:
    return this->b2();
  }
}

/*
 * Perform a move operation on using a Move index.
 */
RubiksCube &RubiksCube ::invert(MOVE ind) {

  switch (ind) {
  case MOVE::L:
    return this->lPrime();
  case MOVE::LPRIME:
    return this->l();
  case MOVE::L2:
    return this->l2();
  case MOVE::R:
    return this->rPrime();
  case MOVE::RPRIME:
    return this->r();
  case MOVE::R2:
    return this->r2();
  case MOVE::U:
    return this->uPrime();
  case MOVE::UPRIME:
    return this->u();
  case MOVE::U2:
    return this->u2();
  case MOVE::D:
    return this->dPrime();
  case MOVE::DPRIME:
    return this->d();
  case MOVE::D2:
    return this->d2();
  case MOVE::F:
    return this->fPrime();
  case MOVE::FPRIME:
    return this->f();
  case MOVE::F2:
    return this->f2();
  case MOVE::B:
    return this->bPrime();
  case MOVE::BPRIME:
    return this->b();
  case MOVE::B2:
    return this->b2();
  }
}

void RubiksCube::print() const {

  cout << "Rubik's Cube:\n\n";

  for (int row = 0; row <= 2; row++) {
    for (unsigned i = 0; i < 7; i++)
      cout << " ";
    for (int col = 0; col <= 2; col++) {
      cout << getColorLetter(getColor(FACE::UP, row, col)) << " ";
    }
    cout << "\n";
  }

  cout << "\n";

  for (int row = 0; row <= 2; row++) {

    for (int col = 0; col <= 2; col++) {
      cout << getColorLetter(getColor(FACE::LEFT, row, col)) << " ";
    }
    cout << " ";

    for (int col = 0; col <= 2; col++) {
      cout << getColorLetter(getColor(FACE::FRONT, row, col)) << " ";
    }
    cout << " ";

    for (int col = 0; col <= 2; col++) {
      cout << getColorLetter(getColor(FACE::RIGHT, row, col)) << " ";
    }
    cout << " ";

    for (int col = 0; col <= 2; col++) {
      cout << getColorLetter(getColor(FACE::BACK, row, col)) << " ";
    }
    cout << "\n";
  }

  cout << "\n";

  for (int row = 0; row <= 2; row++) {
    for (unsigned i = 0; i < 7; i++)
      cout << " ";
    for (int col = 0; col <= 2; col++) {
      cout << getColorLetter(getColor(FACE::DOWN, row, col)) << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}

vector<RubiksCube::MOVE> RubiksCube::randomShuffleCube(unsigned int times) {
  vector<MOVE> moves_performed;
  srand(time(0));
  for (unsigned int i = 0; i < times; i++) {
    unsigned int selectMove = (rand() % 18);
    moves_performed.push_back(static_cast<MOVE>(selectMove));
    this->move(static_cast<MOVE>(selectMove));
  }
  return moves_performed;
}

// Helper function returns string of corner
string RubiksCube::getCornerColorString(uint8_t ind) const {
  string str = "";

  switch (ind) {
    //        UFR
  case 0:
    str += getColorLetter(getColor(FACE::UP, 2, 2));
    str += getColorLetter(getColor(FACE::FRONT, 0, 2));
    str += getColorLetter(getColor(FACE::RIGHT, 0, 0));
    break;

    //            UFL
  case 1:
    str += getColorLetter(getColor(FACE::UP, 2, 0));
    str += getColorLetter(getColor(FACE::FRONT, 0, 0));
    str += getColorLetter(getColor(FACE::LEFT, 0, 2));
    break;

    //            UBL
  case 2:
    str += getColorLetter(getColor(FACE::UP, 0, 0));
    str += getColorLetter(getColor(FACE::BACK, 0, 2));
    str += getColorLetter(getColor(FACE::LEFT, 0, 0));
    break;

    //            UBR
  case 3:
    str += getColorLetter(getColor(FACE::UP, 0, 2));
    str += getColorLetter(getColor(FACE::BACK, 0, 0));
    str += getColorLetter(getColor(FACE::RIGHT, 0, 2));
    break;

    //            DFR
  case 4:
    str += getColorLetter(getColor(FACE::DOWN, 0, 2));
    str += getColorLetter(getColor(FACE::FRONT, 2, 2));
    str += getColorLetter(getColor(FACE::RIGHT, 2, 0));
    break;

    //            DFL
  case 5:
    str += getColorLetter(getColor(FACE::DOWN, 0, 0));
    str += getColorLetter(getColor(FACE::FRONT, 2, 0));
    str += getColorLetter(getColor(FACE::LEFT, 2, 2));
    break;

    //            DBR
  case 6:
    str += getColorLetter(getColor(FACE::DOWN, 2, 2));
    str += getColorLetter(getColor(FACE::BACK, 2, 0));
    str += getColorLetter(getColor(FACE::RIGHT, 2, 2));
    break;

    //            DBL
  case 7:
    str += getColorLetter(getColor(FACE::DOWN, 2, 0));
    str += getColorLetter(getColor(FACE::BACK, 2, 2));
    str += getColorLetter(getColor(FACE::LEFT, 2, 0));
    break;
  }
  return str;
}

void RubiksCube::getCornerColors(uint8_t ind, COLOR &c_ud, COLOR &c_fb,
                                 COLOR &c_lr) const {
  switch (ind) {
    //        UFR
  case 0:
    c_ud = getColor(FACE::UP, 2, 2);
    c_fb = getColor(FACE::FRONT, 0, 2);
    c_lr = getColor(FACE::RIGHT, 0, 0);
    break;

    //            UFL
  case 1:
    c_ud = getColor(FACE::UP, 2, 0);
    c_fb = getColor(FACE::FRONT, 0, 0);
    c_lr = getColor(FACE::LEFT, 0, 2);
    break;

    //            UBL
  case 2:
    c_ud = getColor(FACE::UP, 0, 0);
    c_fb = getColor(FACE::BACK, 0, 2);
    c_lr = getColor(FACE::LEFT, 0, 0);
    break;

    //            UBR
  case 3:
    c_ud = getColor(FACE::UP, 0, 2);
    c_fb = getColor(FACE::BACK, 0, 0);
    c_lr = getColor(FACE::RIGHT, 0, 2);
    break;

    //            DFR
  case 4:
    c_ud = getColor(FACE::DOWN, 0, 2);
    c_fb = getColor(FACE::FRONT, 2, 2);
    c_lr = getColor(FACE::RIGHT, 2, 0);
    break;

    //            DFL
  case 5:
    c_ud = getColor(FACE::DOWN, 0, 0);
    c_fb = getColor(FACE::FRONT, 2, 0);
    c_lr = getColor(FACE::LEFT, 2, 2);
    break;

    //            DBR
  case 6:
    c_ud = getColor(FACE::DOWN, 2, 2);
    c_fb = getColor(FACE::BACK, 2, 0);
    c_lr = getColor(FACE::RIGHT, 2, 2);
    break;

    //            DBL
  case 7:
    c_ud = getColor(FACE::DOWN, 2, 0);
    c_fb = getColor(FACE::BACK, 2, 2);
    c_lr = getColor(FACE::LEFT, 2, 0);
    break;
  }
}

uint8_t RubiksCube::getCornerIndex(uint8_t ind) const {
  COLOR c_ud, c_fb, c_lr;
  getCornerColors(ind, c_ud, c_fb, c_lr);
  uint8_t ret = 0;

  if (c_ud == COLOR::YELLOW || c_fb == COLOR::YELLOW || c_lr == COLOR::YELLOW)
    ret |= (1 << 2);
  if (c_ud == COLOR::ORANGE || c_fb == COLOR::ORANGE || c_lr == COLOR::ORANGE)
    ret |= (1 << 1);
  if (c_ud == COLOR::GREEN || c_fb == COLOR::GREEN || c_lr == COLOR::GREEN)
    ret |= (1 << 0);

  return ret;
}

uint8_t RubiksCube::getCornerOrientation(uint8_t ind) const {
  COLOR c_ud, c_fb, c_lr;
  getCornerColors(ind, c_ud, c_fb, c_lr);

  COLOR c_wy;
  if (c_ud == COLOR::WHITE || c_ud == COLOR::YELLOW)
    c_wy = c_ud;
  else if (c_fb == COLOR::WHITE || c_fb == COLOR::YELLOW)
    c_wy = c_fb;
  else
    c_wy = c_lr;

  if (c_fb == c_wy)
    return 1;
  else if (c_lr == c_wy)
    return 2;
  else
    return 0;
}

// Returns 2-char color string for edge at position ind
// Edge order: UF, UR, UB, UL, FR, FL, BR, BL, DF, DR, DB, DL
string RubiksCube::getEdgeColorString(uint8_t ind) const {
  string str = "";
  switch (ind) {
  case 0: // UF
    str += getColorLetter(getColor(FACE::UP, 2, 1));
    str += getColorLetter(getColor(FACE::FRONT, 0, 1));
    break;
  case 1: // UR
    str += getColorLetter(getColor(FACE::UP, 1, 2));
    str += getColorLetter(getColor(FACE::RIGHT, 0, 1));
    break;
  case 2: // UB
    str += getColorLetter(getColor(FACE::UP, 0, 1));
    str += getColorLetter(getColor(FACE::BACK, 0, 1));
    break;
  case 3: // UL
    str += getColorLetter(getColor(FACE::UP, 1, 0));
    str += getColorLetter(getColor(FACE::LEFT, 0, 1));
    break;
  case 4: // FR
    str += getColorLetter(getColor(FACE::FRONT, 1, 2));
    str += getColorLetter(getColor(FACE::RIGHT, 1, 0));
    break;
  case 5: // FL
    str += getColorLetter(getColor(FACE::FRONT, 1, 0));
    str += getColorLetter(getColor(FACE::LEFT, 1, 2));
    break;
  case 6: // BR
    str += getColorLetter(getColor(FACE::BACK, 1, 0));
    str += getColorLetter(getColor(FACE::RIGHT, 1, 2));
    break;
  case 7: // BL
    str += getColorLetter(getColor(FACE::BACK, 1, 2));
    str += getColorLetter(getColor(FACE::LEFT, 1, 0));
    break;
  case 8: // DF
    str += getColorLetter(getColor(FACE::DOWN, 0, 1));
    str += getColorLetter(getColor(FACE::FRONT, 2, 1));
    break;
  case 9: // DR
    str += getColorLetter(getColor(FACE::DOWN, 1, 2));
    str += getColorLetter(getColor(FACE::RIGHT, 2, 1));
    break;
  case 10: // DB
    str += getColorLetter(getColor(FACE::DOWN, 2, 1));
    str += getColorLetter(getColor(FACE::BACK, 2, 1));
    break;
  case 11: // DL
    str += getColorLetter(getColor(FACE::DOWN, 1, 0));
    str += getColorLetter(getColor(FACE::LEFT, 2, 1));
    break;
  }
  return str;
}
// Returns which of the 12 edge cubies is at position ind (0-11)
// Encoded as: bit2=Yellow/White, bit1=Orange/Red, bit0=Blue/Green
// Same encoding logic as getCornerIndex
static const int8_t edgeLookup[6][6] = {
    //   W   G   R   B   O   Y
    {-1, 3, 0, 1, 2, -1},   // W
    {3, -1, 5, -1, 7, 11},  // G
    {0, 5, -1, 4, -1, 8},   // R
    {1, -1, 4, -1, 6, 9},   // B
    {2, 7, -1, 6, -1, 10},  // O
    {-1, 11, 8, 9, 10, -1}, // Y
};

static inline int colorCharToIndex(char c) {
  switch (c) {
  case 'W':
    return 0;
  case 'G':
    return 1;
  case 'R':
    return 2;
  case 'B':
    return 3;
  case 'O':
    return 4;
  case 'Y':
    return 5;
  default:
    return -1;
  }
}

// In RubiksCube.cpp — avoid heap allocation
uint8_t RubiksCube::getEdgeIndex(uint8_t ind) const {
  // Read colors directly without building a string
  COLOR c1, c2;
  switch (ind) {
  case 0:
    c1 = getColor(FACE::UP, 2, 1);
    c2 = getColor(FACE::FRONT, 0, 1);
    break;
  case 1:
    c1 = getColor(FACE::UP, 1, 2);
    c2 = getColor(FACE::RIGHT, 0, 1);
    break;
  case 2:
    c1 = getColor(FACE::UP, 0, 1);
    c2 = getColor(FACE::BACK, 0, 1);
    break;
  case 3:
    c1 = getColor(FACE::UP, 1, 0);
    c2 = getColor(FACE::LEFT, 0, 1);
    break;
  case 4:
    c1 = getColor(FACE::FRONT, 1, 2);
    c2 = getColor(FACE::RIGHT, 1, 0);
    break;
  case 5:
    c1 = getColor(FACE::FRONT, 1, 0);
    c2 = getColor(FACE::LEFT, 1, 2);
    break;
  case 6:
    c1 = getColor(FACE::BACK, 1, 0);
    c2 = getColor(FACE::RIGHT, 1, 2);
    break;
  case 7:
    c1 = getColor(FACE::BACK, 1, 2);
    c2 = getColor(FACE::LEFT, 1, 0);
    break;
  case 8:
    c1 = getColor(FACE::DOWN, 0, 1);
    c2 = getColor(FACE::FRONT, 2, 1);
    break;
  case 9:
    c1 = getColor(FACE::DOWN, 1, 2);
    c2 = getColor(FACE::RIGHT, 2, 1);
    break;
  case 10:
    c1 = getColor(FACE::DOWN, 2, 1);
    c2 = getColor(FACE::BACK, 2, 1);
    break;
  case 11:
    c1 = getColor(FACE::DOWN, 1, 0);
    c2 = getColor(FACE::LEFT, 2, 1);
    break;
  }
  return edgeLookup[(int)c1][(int)c2];
}

uint8_t RubiksCube::getEdgeOrientation(uint8_t ind) const {
  COLOR c1;
  switch (ind) {
  case 0:
    c1 = getColor(FACE::UP, 2, 1);
    break;
  case 1:
    c1 = getColor(FACE::UP, 1, 2);
    break;
  case 2:
    c1 = getColor(FACE::UP, 0, 1);
    break;
  case 3:
    c1 = getColor(FACE::UP, 1, 0);
    break;
  case 4:
    c1 = getColor(FACE::FRONT, 1, 2);
    break;
  case 5:
    c1 = getColor(FACE::FRONT, 1, 0);
    break;
  case 6:
    c1 = getColor(FACE::BACK, 1, 0);
    break;
  case 7:
    c1 = getColor(FACE::BACK, 1, 2);
    break;
  case 8:
    c1 = getColor(FACE::DOWN, 0, 1);
    break;
  case 9:
    c1 = getColor(FACE::DOWN, 1, 2);
    break;
  case 10:
    c1 = getColor(FACE::DOWN, 2, 1);
    break;
  case 11:
    c1 = getColor(FACE::DOWN, 1, 0);
    break;
  }
  // U/D layer slots: W or Y should face up/down
  if (ind <= 3 || ind >= 8)
    return (c1 == COLOR::WHITE || c1 == COLOR::YELLOW) ? 0 : 1;
  // Middle layer slots: R or O should face front/back
  return (c1 == COLOR::RED || c1 == COLOR::ORANGE) ? 0 : 1;
}