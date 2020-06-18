#include "../board_evaluator.hpp"
#include "../prefix_trie.hpp"
#include "catch.hpp"

#include <iostream>
#include <string>

namespace boggle {

TEST_CASE("FindWordWithDoubleLetter", "[board_evaluator]") {
  PrefixTrie lexicon;
  lexicon.Insert("into");
  BoardEvaluator evaluator(2, 2, std::move(lexicon), [](int) { return 1; });
  std::vector<BoardEvaluator::Square> board = {{'i', 'n'}, {'t', ' '}, {'o', ' '}, {'z', ' '}};
  auto words = evaluator.FindWords(board);
  REQUIRE(words.size() == 1);
  REQUIRE(words.count("into") == 1);
}

TEST_CASE("FindWords4x4", "[board_evaluator][large]") {
  BoardEvaluator evaluator(4, 4, FromFile("lexicons/english.txt"), [](int) { return 1; });
  std::vector<BoardEvaluator::Square> board
      = {{'a', ' '}, {'t', ' '}, {'q', 'u'}, {'v', ' '}, {'r', ' '}, {'s', ' '},
         {'n', ' '}, {'i', ' '}, {'x', ' '}, {'i', ' '}, {'s', ' '}, {'e', ' '},
         {'s', ' '}, {'s', ' '}, {'l', ' '}, {'m', ' '}};
  auto words = evaluator.FindWords(board);
  int num_words = evaluator.Evaluate(board);

  // Solution generated from an independently implemented solver, and verified against current
  // lexicon.
  std::vector<std::string> expected_words
      = {"ar",      "aril",     "arils",   "aris",   "arise",     "arisen",  "ars",     "arsine",
         "arsines", "arsis",    "art",     "arts",   "artsiness", "as",      "asquint", "ass",
         "assent",  "at",       "ats",     "el",     "elint",     "elints",  "elm",     "elms",
         "els",     "elsin",    "elsins",  "em",     "ems",       "en",      "ens",     "entasis",
         "entrism", "ents",     "es",      "ess",    "in",        "inisle",  "inisles", "ins",
         "insist",  "instar",   "intra",   "is",     "isle",      "isles",   "ism",     "issei",
         "lei",     "leis",     "lenis",   "lens",   "lent",      "les",     "less",    "li",
         "lin",     "line",     "lines",   "lins",   "lint",      "lints",   "lira",    "liras",
         "lis",     "list",     "me",      "mein",   "meins",     "meint",   "mel",     "mels",
         "men",     "mensa",    "ment",    "menta",  "mes",       "mess",    "ne",      "nelis",
         "ness",    "nie",      "nies",    "nil",    "nils",      "nis",     "nisei",   "nisi",
         "nisse",   "nix",      "quin",    "quine",  "quines",    "quins",   "quint",   "quinta",
         "quintar", "quintars", "quintas", "quints", "ras",       "rasse",   "rassle",  "rast",
         "rat",     "rats",     "rile",    "riles",  "rin",       "rine",    "rines",   "rins",
         "rinse",   "rise",     "risen",   "sar",    "sari",      "sarin",   "sarins",  "saris",
         "sat",     "sei",      "sel",     "sels",   "sen",       "sens",    "sensa",   "sensi",
         "sensis",  "sent",     "sents",   "si",     "sien",      "siens",   "sient",   "sients",
         "sile",    "silen",    "sileni",  "silens", "silent",    "silents", "siles",   "sin",
         "sine",    "sines",    "sins",    "sir",    "sirs",      "sis",     "siss",    "sist",
         "sista",   "sistra",   "six",     "snies",  "snirt",     "snirts",  "squint",  "sri",
         "sris",    "st",       "star",    "strine", "strines",   "ta",      "tar",     "tars",
         "tarsi",   "tas",      "tass",    "tasse",  "tassel",    "tassels", "tassie",  "trass",
         "trin",    "trine",    "trines",  "trins",  "tsar",      "tsarism", "vie",     "vies",
         "vin",     "vine",     "vines",   "vins",   "vint",      "vints",   "vis",     "vise",
         "visile",  "visne",    "xi",      "xis"};
  REQUIRE(num_words == expected_words.size());
  REQUIRE(words.size() == expected_words.size());
  for (auto expected_word : expected_words) {
    INFO("Checking for word " << expected_word);
    CHECK(words.count(expected_word) == 1);
  }
}

}  // namespace boggle
