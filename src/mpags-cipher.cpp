// Standard Library includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// For std::isalpha and std::isupper
#include <cctype>

// Include header files of user-defined functions
#include "TransformChar.hpp"
#include "ProcessCmdLine.hpp"
#include "RunCaesarCipher.hpp"

// Main function of the mpags-cipher program
int main(int argc, char* argv[])
{
  // Convert the command-line arguments into a more easily usable form
  const std::vector<std::string> cmdLineArgs {argv, argv+argc};

  // Options that might be set by the command-line arguments
  bool helpRequested {false};
  bool versionRequested {false};
  std::string inputFile {""};
  std::string outputFile {""};
  bool encrypt{true};
  size_t k{0};

  // Call function to handle parsing of command line, quits program if an error occurs parsing command line
  bool cmdLinePars {processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile, encrypt, k)};
  if (cmdLinePars==false){
    return 1;
  }

  // Handle help, if requested
  if (helpRequested) {
    // Line splitting for readability
    std::cout
      << "Usage: mpags-cipher [-i <file>] [-o <file>]\n\n"
      << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      << "Available options:\n\n"
      << "  -h|--help        Print this help message and exit\n\n"
      << "  --version        Print version information\n\n"
      << "  -i FILE          Read text to be processed from FILE\n"
      << "                   Stdin will be used if not supplied\n\n"
      << "  -o FILE          Write processed text to FILE\n"
      << "                   Stdout will be used if not supplied\n\n";
    // Help requires no further action, so return from main
    // with 0 used to indicate success
    return 0;
  }
  // Handle version, if requested
  // Like help, requires no further action,
  // so return from main with zero to indicate success
  if (versionRequested) {
    std::cout << "0.1.0" << std::endl;
    return 0;
  }

  // Initialise variables for processing input text
  char inputChar {'x'};
  std::string inputText {""};

  // Read in user input from stdin/file, exits with error message if problem opening file
  if (!inputFile.empty()) {
    std::ifstream in_file {inputFile};
    bool ok_to_read = in_file.good();
    if(ok_to_read)
    {
      // Loop over each character input file
      while(in_file >> inputChar)
        {
          inputText += transformChar(inputChar);
        }
      in_file.close();
    }
    else
    {
      std::cout << "Problem opening the input file" << std::endl;
      return 1;
    }
  }
  else{
    // Loop over each character from user input
    // (until Return then CTRL-D (EOF) pressed)
    while(std::cin >> inputChar)
    {
      inputText += transformChar(inputChar);
    }
  }

  // Implement encryption/decryption 
  std::string outputText{runCaesarCipher(inputText, k, encrypt)};


  // Output the transliterated text, exits with error message if problem opening file
  if (!outputFile.empty()) {
    std::ofstream out_file {outputFile};
    bool ok_to_write = out_file.good();
    if(ok_to_write)
    {
      out_file << outputText << std::endl;
    }
    else{
      std::cout << "There was a problem opening the output file" << std::endl;
      return 1;
    }
    out_file.close(); 
  }
  else{
    std::cout << outputText << std::endl;
  }
  // No requirement to return from main, but we do so for clarity
  // and for consistency with other functions
  return 0;
}
