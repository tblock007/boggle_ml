#include "cubeset.hpp"

#include <algorithm>
#include <cassert>
#include <numeric>

namespace boggle {
namespace {
Cubeset::Cube CreateCube(std::vector<std::string> faces) {
  assert(faces.size() == 6);
  Cubeset::Cube result;
  for (int i = 0; i < faces.size(); ++i) {
    assert(faces[i].size() == 1 || faces[i].size() == 2);
    if (faces[i].size() == 1) {
      result[i] = std::make_pair(faces[i][0], ' ');
    } else if (faces[i].size() == 2) {
      result[i] = std::make_pair(faces[i][0], faces[i][1]);
    } else {
      assert(false);
    }
  }
  return result;
}
}  // namespace

Cubeset::Cubeset(std::vector<Cubeset::Cube> cubes)
    : rd_(),
      mt_engine_(rd_()),
      dice_rolls_(0, 5),
      cubes_(std::move(cubes)),
      indices_(cubes_.size()) {
  std::iota(indices_.begin(), indices_.end(), 0);
}

std::vector<Cubeset::Square> Cubeset::GenerateBoard() {
  std::vector<Cubeset::Square> result(cubes_.size());
  std::shuffle(indices_.begin(), indices_.end(), mt_engine_);
  for (int i = 0; i < cubes_.size(); ++i) {
    size_t face = dice_rolls_(mt_engine_);
    result[indices_[i]] = cubes_[i][face];
  }
  return result;
}

Cubeset FiveByFive() {
  std::vector<Cubeset::Cube> cubes{
      CreateCube({"a", "a", "e", "e", "e", "e"}),  CreateCube({"e", "m", "o", "t", "t", "t"}),
      CreateCube({"i", "k", "l", "qu", "u", "w"}), CreateCube({"c", "e", "i", "l", "p", "t"}),
      CreateCube({"d", "d", "h", "n", "o", "t"}),  CreateCube({"a", "e", "e", "e", "e", "m"}),
      CreateCube({"f", "i", "p", "r", "s", "y"}),  CreateCube({"d", "h", "h", "l", "n", "o"}),
      CreateCube({"d", "h", "h", "l", "o", "r"}),  CreateCube({"a", "d", "e", "n", "n", "n"}),
      CreateCube({"c", "c", "e", "n", "s", "t"}),  CreateCube({"n", "o", "o", "u", "t", "w"}),
      CreateCube({"o", "o", "o", "t", "u", "u"}),  CreateCube({"b", "j", "k", "qu", "x", "z"}),
      CreateCube({"c", "e", "i", "p", "s", "t"}),  CreateCube({"a", "f", "i", "r", "s", "y"}),
      CreateCube({"e", "i", "i", "t", "t", "t"}),  CreateCube({"a", "e", "e", "g", "m", "u"}),
      CreateCube({"g", "o", "r", "r", "v", "w"}),  CreateCube({"c", "e", "i", "i", "l", "t"}),
      CreateCube({"a", "a", "a", "f", "r", "s"}),  CreateCube({"a", "a", "f", "i", "r", "s"}),
      CreateCube({"a", "e", "g", "m", "n", "n"}),  CreateCube({"d", "h", "l", "n", "o", "r"}),
      CreateCube({"e", "n", "s", "s", "s", "u"})};
  return Cubeset(std::move(cubes));
}

}  // namespace boggle