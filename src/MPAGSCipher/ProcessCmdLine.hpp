#ifndef MPAGSCIPHER_PROCESSCMDLINE_HPP
#define MPAGSCIPHER_PROCESSCMDLINE_HPP
#include<vector>
#include <string>

bool processCommandLine(
  const std::vector<std::string>& args,
  bool& helpRequested,
  bool& versionRequested,
  std::string& inputFileName,
  std::string& outputFileName, 
  bool& encrypt,
  size_t& key );

#endif // MPAGSCIPHER_PROCESSCMDLINE_HPP