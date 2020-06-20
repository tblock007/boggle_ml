#ifndef CUBESET_HPP
#define CUBESET_HPP

#include <array>
#include <random>
#include <utility>
#include <vector>

namespace boggle {

// ********************************************************************************
/// <summary>
/// Represents a set of cubes used to generate a Boggle board.
/// </summary>
// ********************************************************************************
class Cubeset {
 public:
  // Represents the face of a cube. A ' ' character in the second slot means this
  // face has only one letter.
  using Square = std::pair<char, char>;
  using Cube = std::array<Square, 6>;

  Cubeset(std::vector<Cube> cubes);

  // Generates a random board from the Cubeset, using a uniform distribution
  // to generate the Cube ordering and Square selection.
  std::vector<Square> GenerateBoard();

 private:
  std::random_device rd_;
  std::mt19937 mt_engine_;
  std::uniform_int_distribution<size_t> dice_rolls_;
  std::vector<Cube> cubes_;
  std::vector<size_t> indices_;
};

// ********************************************************************************
/// <summary>
/// Creates the 25 cubeset that is used in official Big Boggle.
/// </summary>
/// <returns>A Cubeset that contains the official Big Boggle cubes.</returns>
// ********************************************************************************
Cubeset FiveByFive();

}  // namespace boggle

#endif  // CUBESET_HPP