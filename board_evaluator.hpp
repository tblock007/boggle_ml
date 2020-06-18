#ifndef BOARD_EVALUATOR_H
#define BOARD_EVALUATOR_H

#include <functional>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "prefix_trie.hpp"

namespace boggle {

// ********************************************************************************
/// <summary>
/// Evaluates a provided board by searching it for all words that occur in the
/// lexicon, and reporting a sum of scores for all words.
///
/// The score function can be specified, and can be used to adjust what kinds of
/// boards are preferred. For example, greater emphasis can be placed on long
/// words than standard Boggle rules by making appropriate adjustments to the
/// score function.
/// </summary>
// ********************************************************************************
class BoardEvaluator {
 public:
  // Represents the face of a cube. A ' ' character in the second slot means this
  // face has only one letter.
  using Square = std::pair<char, char>;

  BoardEvaluator(int width, int height, PrefixTrie&& lexicon,
                 std::function<int(int)> score_function);

  std::unordered_set<std::string> FindWords(std::vector<Square> const& board);
  int Evaluate(std::vector<Square> const& board);

 private:
  std::unordered_set<std::string> DfsTrieTraverse(std::vector<Square> const& board, int index,
                                                  std::vector<char> visited, TrieNode* trie_node);

  int const width_;
  int const height_;
  PrefixTrie lexicon_;
  std::function<int(int)> score_function_;

  std::vector<std::vector<int>> adj_list_;
};

}  // namespace boggle

#endif  // BOARD_EVALUATOR_HPP