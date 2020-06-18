#ifndef PREFIX_TRIE_HPP
#define PREFIX_TRIE_HPP

#include <memory>
#include <string_view>
#include <vector>

namespace boggle {

// ********************************************************************************
/// <summary>
/// Represents one node of the PrefixTrie. Connections to other nodes represent
/// the letters of the word. i.e., a TrieNode actually corresponds to the spaces
/// between the letters, not the letters themselves.
/// </summary>
// ********************************************************************************
class TrieNode {
 public:
  TrieNode();

  void Insert(std::string_view partial_word);
  bool IsWord(std::string_view partial_word);

 private:
  std::vector<std::unique_ptr<TrieNode>> children_;
  bool is_word_;

  // BoardEvaluator performs its own traversal of the PrefixTrie in its word-finding
  // algorithm.
  friend class BoardEvaluator;
};

// ********************************************************************************
/// <summary>
/// Data structure that stores a lexicon of words. Provides O(N) lookup and O(N)
/// insert, where N is the number of characters in the word.
/// </summary>
// ********************************************************************************
class PrefixTrie {
 public:
  void Insert(std::string_view word);
  bool IsWord(std::string_view word);

 private:
  TrieNode root_;

  // BoardEvaluator performs its own traversal of the PrefixTrie in its word-finding
  // algorithm.
  friend class BoardEvaluator;
};

// ********************************************************************************
/// <summary>
/// Loads a list of words from a text file into the PrefixTrie. This function
/// assumes that the file is properly formatted with one word per line, and only
/// lowercase letters. Behavior is undefined otherwise.
/// </summary>
/// <param name="path">The path to the file containing the list of words.</param>
/// <returns>The PrefixTrie populated with the list of words.</returns>
// ********************************************************************************
PrefixTrie FromFile(std::string path);

}  // namespace boggle

#endif  // PREFIX_TRIE_HPP