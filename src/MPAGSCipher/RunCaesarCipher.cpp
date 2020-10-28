#include <iostream>
#include <string>
#include <cctype>
#include <vector>

#include "RunCaesarCipher.hpp"

std::string runCaesarCipher(const std::string& inputText, const size_t key, const bool encrypt){
    // Initialize variables to hold output, and positiong of input character in the alphabet
    int pos;
    std::string output{""};
    // Initialize std::vector<char> to hold the alphabet
    std::vector<char> alphabet{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    size_t alphlen{alphabet.size()};
    
    // Loop over the input text to be encrypted/decrypted
    for(size_t i{0}; i < inputText.length(); ++i){

        // Loop over alphabet container to find position of input character in the alphaber
        for(size_t j{0}; j < alphlen; ++j){
            if (inputText[i]==alphabet[j]){
                pos = j;
                break;
            }
        }

        // Translate plaintext to ciphertext if encrypt is true, otherwise decrypt ciphertext
        if(encrypt){
            pos += key;
        }
        else{
            pos += -key + alphlen;
        }
        pos = pos%alphlen;

        // Add encrypted/decrypted character to the output string
        output += alphabet[pos];
    }
    return output;
}