#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "ProcessCmdLine.hpp"

bool processCommandLine(
  const std::vector<std::string>& args,
  bool& helpRequested,
  bool& versionRequested,
  std::string& inputFileName,
  std::string& outputFileName,
  bool& encrypt,
  size_t& key )
{
  /* Parse the command line arguments, checking for help or version, otherwise deal with input and output file names
    args: Vector containing the command line arguments as strings
    helpRequested: Set to true if "-h" or "--help" in args
    versionRequested: Set to true if "--version" in args
    inputFileName: if "-i" in args, set to next value in args
    outputFileName: if "-o" in args, set to next value in args
    encrypt: if "--decrypt" in args, set to false, default value is true
    key: if "-k" in args, set to next value in args

    return: bool variable to check if function exectuted without errors
  */
  // Add a typedef that assigns another name for the given type for clarity
  typedef std::vector<std::string>::size_type size_type;
  const size_type nCmdLineArgs {args.size()};
  int e_dCheck{0};
  // Process command line arguments - ignore zeroth element, as we know this to
  // be the program name and don't need to worry about it
  for (size_type i {1}; i < nCmdLineArgs; ++i) {

    if (args[i] == "-h" || args[i] == "--help") {
      helpRequested = true;
    }
    else if (args[i] == "--version") {
      versionRequested = true;
    }
    else if (args[i] == "-i") {
      // Handle input file option
      // Next element is filename unless -i is the last argument
      if (i == nCmdLineArgs-1) {
	      std::cerr << "[error] -i requires a filename argument" << std::endl;
	      // exit main with non-zero return to indicate failure
	      return false;
      }
      else {
	      // Got filename, so assign value and advance past it
	      inputFileName = args[i+1];
	      ++i;
      }
    }
    else if (args[i] == "-o") {
      // Handle output file option
      // Next element is filename unless -o is the last argument
      if (i == nCmdLineArgs-1) {
	      std::cerr << "[error] -o requires a filename argument" << std::endl;
	      // exit main with non-zero return to indicate failure
	      return false;
      }
      else {
	      // Got filename, so assign value and advance past it
	      outputFileName = args[i+1];
	      ++i;
      }
    }
    else if (args[i] == "--decrypt" || args[i]== "--encrypt"){
      if(e_dCheck==0){
        if(args[i] == "--decrypt"){
          encrypt = false;
        }
        e_dCheck += 1;
      }
      // Handle error if multiple occurences of "--decrypt" or "--encrypt"
      else{
        std::cerr << "[error] --encrypt/--decrypt has benn specfied more than once" << std::endl;
      }
    }
    else if (args[i] == "-k") {
      // Handle key option
      // Next element is the key unless -k is the last argument
      if (i == nCmdLineArgs-1) {
	      std::cerr << "[error] -k requires an unsigned integer argument" << std::endl;
	      // exit main with non-zero return to indicate failure
	      return false;
      }
      else {
	      // Got key, so assign value and advance past it
        // Also deal with possible wrap-around of key
	      key = std::stoull(args[i+1]);
        key = key%26;
	      ++i;
      }
    }
    else {
      // Have an unknown flag to output error message and return non-zero
      // exit status to indicate failure
      std::cerr << "[error] unknown argument '" << args[i] << "'\n";
      return false;
    }
  }
  return true;
}