#include <string>

#include <cctype>

#include "TransformChar.hpp"

std::string transformChar(const char in_char)
{
  /* Function to change an input character to uppercase if alphanumeric, ignored otherwise, and returned in a string

    char in_char: Input character to be checked and/or converted

    return: The converted character as a string.*/

    std::string input{""};
    // Uppercase alphabetic characters
    if (std::isalpha(in_char)) {
      input += std::toupper(in_char);
      return input;
    }

    // Transliterate digits to English words
    switch (in_char) {
      case '0':
	      input += "ZERO";
	      break;
      case '1':
	      input += "ONE";
	      break;
      case '2':
	      input += "TWO";
	      break;
      case '3':
	      input += "THREE";
	      break;
      case '4':
	      input += "FOUR";
	      break;
      case '5':
	      input += "FIVE";
	      break;
      case '6':
	      input += "SIX";
	      break;
      case '7':
	      input += "SEVEN";
	      break;
      case '8':
	      input += "EIGHT";
	      break;
      case '9':
	      input += "NINE";
	      break;
    }
  return input;
    // If the character isn't alphabetic or numeric, DONT add it.
    // Our ciphers can only operate on alphabetic characters.
}