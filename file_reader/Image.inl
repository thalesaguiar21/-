#include "Image.h"

namespace filerd {
  Image::Image( void ) {
    name = "";
    format = "";
    width = 0;
    height = 0;
    aliasSamples = 0;
  }

  Image::Image( string name_, string format_, string cod_, int width_,
                int height_, int aliasSamples_ ) {
    name = name_;
    format = format_;
    cod = cod_;
    width = (width_ < 0) ? (0) : (width_);
    height = (height_ < 0) ? (0) : (height_);
    aliasSamples = (aliasSamples_ < 0) ? (0) : (aliasSamples_);
  }

  string Image::Header() {
    if(format.compare("PPM")) {
      return  "P3\n" + std::to_string(width) + " "
              + std::to_string(height) + "\n255\n";
    } else {
      cout << UNSUPPORTED_FORMAT << endl;
      return "";
    }
  }

  void Image::FromContent( vector<string> fileContent ) {
    if (ValidateContent(fileContent)) {
      vector<string> tmpContnt = RemoveComents(fileContent);
      name = tmpContnt[NAME].substr(7, tmpContnt[NAME].length());
      format = tmpContnt[TYPE].substr(7, tmpContnt[TYPE].length());

      int codLength = tmpContnt[CODIFICATION].length();
      cod = tmpContnt[CODIFICATION].substr(15, codLength);

      int widthLength = tmpContnt[WIDTH].length();
      width 	= std::stoi(tmpContnt[WIDTH].substr(8, widthLength), nullptr);

      int heightLength = tmpContnt[HEIGHT].length();
      height 	= std::stoi(tmpContnt[HEIGHT].substr(9, heightLength), nullptr);

      int aliasLength = tmpContnt[ALIAS].length();
      aliasSamples 	= std::stoi(tmpContnt[ALIAS].substr(9, aliasLength), nullptr);
    }
  }

} // namespace filerd
