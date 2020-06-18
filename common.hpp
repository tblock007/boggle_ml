#ifndef COMMON_HPP
#define COMMON_HPP

namespace boggle {

static constexpr unsigned int NUM_LETTERS = 26;

// ********************************************************************************
/// <summary>
/// Performs conversion from a character (i.e., a letter in a word) to an
/// index that can be used to access arrays or vectors whose elements are
/// intended to correspond to letters.
/// </summary>
/// <remarks>
/// For performance reasons, due to the frequency at which this conversion
/// will occur, this function assumes that the character will fall within
/// the range ['a','z'], and no checks are performed to validate this. Calling
/// code is responsible for ensuring that this is not violated.
/// </remarks>
/// <param name="c">The character to convert.</param>
/// <returns>An integer index corresponding to the character.</returns>
// ********************************************************************************
constexpr inline unsigned int CharToIndex(char c) {
  return static_cast<int>(c) - 'a';
}

}  // namespace boggle

#endif  // COMMON_HPP