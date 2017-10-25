#include "Image.h"

namespace filerd {
  Image::Image( void ) {
    name = "";
    format = "";
    width = 0;
    height = 0;
    aliasSamples = 1;
  }

  Image::Image( string name_, string format_, string cod_, int width_,
                int height_, int aliasSamples_ ) {
    name = name_;
    format = format_;
    cod = cod_;
    width = (width_ < 0) ? (0) : (width_);
    height = (height_ < 0) ? (0) : (height_);
    aliasSamples = std::max(1, aliasSamples_);
  }

  string Image::Header() {
    if(format.compare("PPM") == 0) {
      return  "P3\n" + std::to_string(width) + " "
              + std::to_string(height) + "\n255\n";
    } else {
      cout << UNSUPPORTED_FORMAT << endl;
      return "";
    }
  }

  string Image::Description() {
    string descr = "";
    descr += "NAME:\t" + name + "\n";
    descr += "SIZE:\t" + std::to_string(width) + "x";
    descr += std::to_string(height) + "\n";
    descr += "ALIAS:\t" + std::to_string(aliasSamples);
    return descr;
  }

  void Image::FromContent( vector<string> fileContent ) {
    if (ValidateContent(fileContent)) {
      vector<string> tmpContnt = RemoveComents(fileContent);
      name = tmpContnt[NAME].substr(7, tmpContnt[NAME].length());
      format = tmpContnt[TYPE].substr(7, tmpContnt[TYPE].length());

      int codLength = tmpContnt[CODIFICATION].length();
      cod = tmpContnt[CODIFICATION].substr(15, codLength);

      int widthLength = tmpContnt[WIDTH].length();
      width = std::stoi(tmpContnt[WIDTH].substr(8, widthLength), nullptr);

      int heightLength = tmpContnt[HEIGHT].length();
      height = std::stoi(tmpContnt[HEIGHT].substr(9, heightLength), nullptr);

      int aliasLength = tmpContnt[ALIAS].length();
      aliasSamples = std::stoi(tmpContnt[ALIAS].substr(8, aliasLength), nullptr);

      content = new int*[height];
      for(auto i = 0; i < height; i++) {
        content[i] = new int[3*width];
      }

      if(aliasSamples <= 0) {
        aliasSamples = 1;
      }
    }
  }

} // namespace filerd
