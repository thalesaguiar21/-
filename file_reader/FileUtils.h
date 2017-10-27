#ifndef _CONSTS_H_
#define _CONSTS_H_

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace file_utils {

  // Namespace constants
  // Error messages
  const string UNSUPPORTED_FORMAT  = "[ERROR] Format is not supported!";
  const string NO_CONTENT          = "[ERROR] No content given!";
  const string INVALID_SIZE        = "[ERROR] Insuficient information, or file is too big!";
  const string INSUFICIENT_CONTENT = "[ERROR] No information given: ";
  // Valid file attributes
  const char COMMENT_CHAR   = '#';
  const int VALID_FILE_SIZE = 6;
  // Atributes position
  enum attr_position { NAME, TYPE, CODIFICATION, WIDTH, HEIGHT, ALIAS };
  // Supported formats
  enum imgFormats { PPM };

  vector<string> RemoveComents( vector<string> &fileContent );
  bool ValidateContent( vector<string> content );

} // namespace file_utils

#include "FileUtils.inl"

#endif