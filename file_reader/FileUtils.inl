#include "FileUtils.h"

namespace file_utils {

  vector<string> RemoveComents(vector<string> &fileContent) {
    vector<short> commentPos;
    
    for(int i = 0; i < fileContent.size(); ++i) {
      int comment_pos = fileContent[i].find_first_of(COMMENT_CHAR);
      // Ignore the line starting from the comment character
      fileContent[i] = fileContent[i].substr(0, comment_pos);
      if(fileContent[i].length() == 0) {
        commentPos.push_back(i);
      }
    }

    // Remove lines that are comment only
    for(short & comment : commentPos) {
      fileContent.erase(fileContent.begin() + comment);
    }

    return fileContent;
  }

  string RemoveSpacingChars(string str) {
    string result = str;
    for(int i=0; i < result.length(); i++) {
      if(str[i] == '\n' || str[i] == '\t') {
        result.erase(i);
      }
    }
    return result;
  };

  vector<string> Split(const string str, const char s) {
    vector<string> result;
    string item = "";
    for(int i=0; i < str.length(); i++) {
      if(str[i] == s) {
        result.push_back(item);
        item = "";
        continue;
      }
      item += str[i];
    }
    result.push_back(item);

    return result;
  }

   /*  
      Returns true if the file has no erros, false otherwise
  */
  bool ValidateContent( vector<string> content ) {
    cout << "Checking file format...";
    bool valid = true;
    RemoveComents(content);
    if(content.empty()) {
      cout << NO_CONTENT << endl;
      valid = false;
    } else if(content.size() != VALID_FILE_SIZE) {
      cout << INVALID_SIZE << " file has #lines: " << content.size() << endl;
      valid = false;
    } else if(content[NAME].substr(0, 4).compare("NAME") != 0) {
      cout << INSUFICIENT_CONTENT << "NAME" << endl;
      valid = false;
    } else if(content[TYPE].substr(0, 4).compare("TYPE") != 0) {
      cout << INSUFICIENT_CONTENT << "TYPE" << endl;
      valid = false;
    } else if(content[CODIFICATION].substr(0, 12).compare("CODIFICATION") != 0) {
      cout << INSUFICIENT_CONTENT << "CODIFICATION" << endl;
      valid = false;
    } else if(content[WIDTH].substr(0, 5).compare("WIDTH") != 0) {
      cout << INSUFICIENT_CONTENT << "WIDTH" << endl;
      valid = false;
    } else if(content[HEIGHT].substr(0, 6).compare("HEIGHT") != 0) {
      cout << INSUFICIENT_CONTENT << "HEIGHT" << endl;
      valid = false;
    } else if(content[ALIAS].substr(0, 5).compare("ALIAS") != 0) {
      cout << INSUFICIENT_CONTENT << "ALIAS" << endl;
      valid = false;
    } else {
      cout << "Success!" << endl;  
    }
    return valid;
  }
} // namespace file_utils