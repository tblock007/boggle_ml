#include "../prefix_trie.hpp"
#include "catch.hpp"

namespace boggle {

TEST_CASE("BasicInsertAndQuery", "[prefix_trie]") {
  PrefixTrie trie;
  trie.Insert("abcd");
  trie.Insert("abcdefg");
  REQUIRE(trie.IsWord("abcd") == true);
  REQUIRE(trie.IsWord("a") == false);
  REQUIRE(trie.IsWord("abcde") == false);
  REQUIRE(trie.IsWord("abcdefg") == true);
  REQUIRE(trie.IsWord("bcdefg") == false);
}

TEST_CASE("EmptyString", "[prefix_trie]") {
  PrefixTrie trie;
  REQUIRE(trie.IsWord("") == false);
  trie.Insert("");
  REQUIRE(trie.IsWord("") == true);
}

TEST_CASE("LoadFromFile", "[prefix_trie]") {
  PrefixTrie trie = FromFile("lexicons/prefix_trie_test.txt");
  REQUIRE(trie.IsWord("banana") == true);
  REQUIRE(trie.IsWord("ban") == true);
  REQUIRE(trie.IsWord("back") == true);
  REQUIRE(trie.IsWord("anana") == true);
  REQUIRE(trie.IsWord("b") == false);
  REQUIRE(trie.IsWord("ba") == false);
  REQUIRE(trie.IsWord("bana") == false);
  REQUIRE(trie.IsWord("banan") == false);
  REQUIRE(trie.IsWord("") == false);
  REQUIRE(trie.IsWord("bananan") == false);
}

}  // namespace boggle
