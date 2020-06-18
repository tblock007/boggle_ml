#include <fstream>
#include <iostream>
#include <string>

#include "common.hpp"
#include "prefix_trie.hpp"

namespace boggle {

TrieNode::TrieNode() : children_(NUM_LETTERS), is_word_(false) {
}

void TrieNode::Insert(std::string_view partial_word) {
  if (partial_word.empty()) {
    is_word_ = true;
    return;
  }

  char next = CharToIndex(partial_word[0]);
  if (children_[next] == nullptr) {
    children_[next] = std::make_unique<TrieNode>();
  }
  children_[next]->Insert(partial_word.substr(1));
}

bool TrieNode::IsWord(std::string_view partial_word) {
  if (partial_word.empty()) {
    return is_word_;
  }

  char next = CharToIndex(partial_word[0]);
  if (children_[next] == nullptr) {
    return false;
  }
  return children_[next]->IsWord(partial_word.substr(1));
}

void PrefixTrie::Insert(std::string_view word) {
  return root_.Insert(word);
}

bool PrefixTrie::IsWord(std::string_view word) {
  return root_.IsWord(word);
}

PrefixTrie FromFile(std::string path) {
  PrefixTrie result;
  std::ifstream file(path);
  std::string word;
  while (file >> word) {
    result.Insert(word);
  }
  return result;
}

}  // namespace boggle