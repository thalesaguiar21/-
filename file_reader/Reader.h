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
  // Reads a file with a given name and creates a Image object with its content.
  bool ReadFile( string file_name, vector<string> &content );
  vector<int> GetValues(string str);
  void WriteOnFile( Image img );
} // namespace filerd

#include "Reader.inl"

#endif
