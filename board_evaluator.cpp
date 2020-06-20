#include "board_evaluator.hpp"
#include "common.hpp"
#include "cubeset.hpp"

namespace boggle {

BoardEvaluator::BoardEvaluator(int width, int height, PrefixTrie&& lexicon,
                               std::function<int(int)> score_function)
    : width_(width),
      height_(height),
      lexicon_(std::move(lexicon)),
      score_function_(std::move(score_function)) {
  // Create an adjacency list to describe valid steps for a path through the Boggle board.
  adj_list_ = std::vector<std::vector<int>>(width * height);
  // Add left-right neighbor relationships.
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width - 1; ++j) {
      adj_list_[i * width + j].push_back(i * width + j + 1);
      adj_list_[i * width + j + 1].push_back(i * width + j);
    }
  }
  // Add top-bottom neighbor relationships.
  for (int i = 0; i < height - 1; ++i) {
    for (int j = 0; j < width; ++j) {
      adj_list_[i * width + j].push_back((i + 1) * width + j);
      adj_list_[(i + 1) * width + j].push_back(i * width + j);
    }
  }
  // Add diagonal neighbor relationships.
  for (int i = 0; i < height - 1; ++i) {
    for (int j = 0; j < width - 1; ++j) {
      adj_list_[i * width + j].push_back((i + 1) * width + j + 1);
      adj_list_[(i + 1) * width + j + 1].push_back(i * width + j);
      adj_list_[i * width + (j + 1)].push_back((i + 1) * width + j);
      adj_list_[(i + 1) * width + j].push_back(i * width + (j + 1));
    }
  }
}

std::unordered_set<std::string> BoardEvaluator::FindWords(
    std::vector<Cubeset::Square> const& board) {
  std::unordered_set<std::string> words;
  for (int i = 0; i < board.size(); ++i) {
    words.merge(
        DfsTrieTraverse(board, i, std::vector<char>(width_ * height_, 0U), &lexicon_.root_));
  }
  return words;
}

int BoardEvaluator::Evaluate(std::vector<Cubeset::Square> const& board) {
  int sum = 0;
  auto words = FindWords(board);
  for (auto word : words) {
    sum += score_function_(static_cast<int>(word.size()));
  }
  return sum;
}

std::unordered_set<std::string> BoardEvaluator::DfsTrieTraverse(
    std::vector<Cubeset::Square> const& board, int index, std::vector<char> visited,
    TrieNode* trie_node) {
  // Ensure that including the current Square could still lead to a valid word, according to the
  // prefix trie. If so, traverse the trie accordingly and continue the DFS. Otherwise, return an
  // empty set to indicate no words can be found by including this Square.
  if (trie_node->children_[CharToIndex(board[index].first)] == nullptr) {
    return std::unordered_set<std::string>();
  }
  std::string base(1, board[index].first);
  TrieNode* next_node = trie_node->children_[CharToIndex(board[index].first)].get();
  if (board[index].second != ' ') {
    if (next_node->children_[CharToIndex(board[index].second)] == nullptr) {
      return std::unordered_set<std::string>();
    }
    base += std::string(1, board[index].second);
    next_node = next_node->children_[CharToIndex(board[index].second)].get();
  }

  std::unordered_set<std::string> words;
  if (next_node->is_word_) {
    words.insert(base);
  }

  for (auto neighbor : adj_list_[index]) {
    if (visited[neighbor] == 0) {
      // TODO: Change this to bitset? Templatize width and height.
      std::vector<char> updated_visited = visited;
      updated_visited[index] = 1;
      auto suffixes = DfsTrieTraverse(board, neighbor, updated_visited, next_node);
      for (auto suffix : suffixes) {
        words.insert(base + suffix);
      }
    }
  }
  return words;
}

}  // namespace boggle