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
  std::string& outputFileName )
{
  /* Parse the command line arguments, checking for help or version, otherwise deal with input and output file names
    args: Vector containing the command line arguments as strings
    helpRequested: Set to true if "-h" or "--help" in args
    versionRequested: Set to true if "--version" in args
    inputFileName: if "-i" in args, set to next value in args
    outputFileName: if "-o" in args, set to next value in args

    return: bool variable to check if function exectuted without errors
  */
  // Add a typedef that assigns another name for the given type for clarity
  typedef std::vector<std::string>::size_type size_type;
  const size_type nCmdLineArgs {args.size()};
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
    else {
      // Have an unknown flag to output error message and return non-zero
      // exit status to indicate failure
      std::cerr << "[error] unknown argument '" << args[i] << "'\n";
      return false;
    }
  }
  return true;
}