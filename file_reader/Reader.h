#ifndef _READER_H_
#define _READER_H_

#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;

/* Example of valid file
 * -----------------------------------------------
 * NAME = test_normalshader_antialias500_01.ppm
 * TYPE = PPM
 * CODIFICATION = binary # aqui poderia ser: ascii
 * WIDTH = 800
 * HEIGHT = 400
 * ALIAS_SAMPLES = 100
 * -----------------------------------------------
 */

namespace filerd {
  // Namespace constants
  // Error messages
  const string UNSUPPORTED_FORMAT  = "[ERROR] Format is not supported!";
  const string NO_CONTENT          = "[ERROR] No content given!";
  const string INVALID_SIZE        = "[ERROR] Insuficient information, or file is too big!";
  const string INSUFICIENT_CONTENT = "[ERROR] No information given: ";
  // Valid file attributes
  const char COMMENT_CHAR   = '#';
  const int VALID_FILE_SIZE = 9;
  // Atributes position
  enum attr_position { NAME, TYPE, CODIFICATION, WIDTH, HEIGHT, ALIAS };
  // Supported formats
  enum imgFormats { PPM };
  // Reads a file with a given name and creates a Image object with its content.
  vector<string> ReadFile( string fileName );
  vector<int> GetValues(string str);
  vector<string> RemoveComents( vector<string> fileContent );
  bool ValidateContent( vector<string> fileContent );
} // namespace filerd

#include "Reader.inl"

#endif
