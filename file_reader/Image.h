#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <iostream>
#include <string>
#include <vector>

#include "FileUtils.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace filerd {
  class Image {
    public:
      int **content;
      string name;
      string format;
      string cod;
      int width;
      int height;
      int aliasSamples;

      Image( void );
      Image( string name, string format, string cod, int width, int height,
             int aliasSamples);
      
      /*  Returns the standard header of the current file format. For example,
          if the current Image is a PPM, then this method will return:

          P3
          width height
          255
      */
      string Header();
      
      string Description();
      bool FromContent( vector<string> fileContent );
    private:
      // Error messages
      const string UNSUPPORTED_FORMAT  = "[ERROR] Format is not supported!";
      const string INVALID_VALUE      = "[ERROR] Invalid value! For attribute ";
      // Supported formats
      string imgFormats[1] { "PPM" };

      bool VerifyValues();
      bool IsFormatSupported( string format );
  };
} // namespace filerd

#include "Image.inl"

#endif
