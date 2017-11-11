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
      cout << file_utils::UNSUPPORTED_FORMAT << endl;
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

  bool Image::IsFormatSupported( string format ) {
    for(string & sFormat : file_utils::imgFormats) {
      if(sFormat.compare(format)) {
        return true;
      }
    }
    return false;
  }

  bool Image::VerifyValues() {
    cout << "Verifying values of image description...";;
    bool isValid = false;
    if(!IsFormatSupported(cod)) {
      cout << file_utils::UNSUPPORTED_FORMAT << endl;
    } else if (width <= 0) {
      cout << file_utils::INVALID_VALUE << " WIDTH." << endl;
    } else if (height <= 0) {
      cout << file_utils::INVALID_VALUE << " HEIGHT." << endl;
    } else if (aliasSamples <= 0) {
      cout << file_utils::INVALID_VALUE << " ANTI-ALIASING SAMPLES." << endl;
    } else {
      cout << "Done!" << endl;
      isValid = true;
    }
    return isValid;
  }

  bool Image::FromContent( vector<string> fileContent ) {
    bool isValid = file_utils::ValidateContent(fileContent);
    if (isValid) {
      vector<string> tmpContnt = file_utils::RemoveComents(fileContent);
      name = tmpContnt[file_utils::NAME].substr(7, 
        tmpContnt[file_utils::NAME].length());
      
      format = tmpContnt[file_utils::TYPE].substr(7, 
        tmpContnt[file_utils::TYPE].length());

      int codLength = tmpContnt[file_utils::CODIFICATION].length();
      cod = tmpContnt[file_utils::CODIFICATION].substr(15, codLength);
      
      int widthLength = tmpContnt[file_utils::WIDTH].length();
      width = std::stoi(tmpContnt[file_utils::WIDTH].substr(8, 
        widthLength), nullptr);

      int heightLength = tmpContnt[file_utils::HEIGHT].length();
      height = std::stoi(tmpContnt[file_utils::HEIGHT].substr(9, 
        heightLength), nullptr);

      int aliasLength = tmpContnt[file_utils::ALIAS].length();
      aliasSamples = std::stoi(tmpContnt[file_utils::ALIAS].substr(8, 
        aliasLength), nullptr);

      content = new int*[height];
      for(auto i = 0; i < height; i++) {
        content[i] = new int[3*width];
      }
      isValid = VerifyValues();
    }
    return isValid;
  }

} // namespace filerd
