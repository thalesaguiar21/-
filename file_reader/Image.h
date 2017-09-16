#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <iostream>
#include <string>
#include <vector>

#include "Reader.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace filerd {
  class Image {
    public:
      string name;
      string format;
      string cod;
      int width;
      int height;
      int aliasSamples;

      Image( void );
      Image(  string name, string format, string cod, int width, int height,
              int aliasSamples);
      string Header();
      void FromContent( vector<string> fileContent );
  };
} // namespace filerd

#include "Image.inl"
#endif
