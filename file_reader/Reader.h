#ifndef _READER_H_
#define _READER_H_

#include <vector>
#include <string>

#include "FileUtils.h"

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
  // Reads a file with a given name and creates a Image object with its content.
  vector<string> ReadFile( string fileName );
  vector<int> GetValues(string str);
  vector<string> RemoveComents( vector<string> fileContent );
  bool ValidateContent( vector<string> fileContent );
  void WriteOnFile( Image img );
} // namespace filerd

#include "Reader.inl"

#endif
