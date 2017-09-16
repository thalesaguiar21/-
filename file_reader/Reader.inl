#include "Reader.h"

namespace filerd {

  vector<string> ReadFile( string file_name ) {
    vector<string> file_lines;
    cout << "Opening file...";
    std::ifstream myfile(file_name);
    if( myfile.is_open() ) {
      string line;
      while( getline(myfile, line) ) {
        file_lines.push_back(line);
      }
    } else {
      cout << "[ERROR] Could not open the file " << file_name << endl;
    }
    myfile.close();
    cout << "Done!" << endl;
    return file_lines;
  }

  vector<int> GetValues(string str) {
    int size = str.length();
    string num = "";
    vector<int> values;

    for(int i = 0; i < size; ++i) {
      if(str[i] != ' ') {
        num += str[i];
      } else if(values.size() < 3) {
        values.push_back(std::stoi(num, nullptr));
        num = "";
      }
    }
    return values;
  }

  vector<string> RemoveComents(vector<string> fileContent) {
    for(int i = 0; i < fileContent.size(); ++i) {
      int comment_pos = fileContent[i].find_first_of(COMMENT_CHAR);
      fileContent[i] = fileContent[i].substr(0, comment_pos);
    }
    return fileContent;
  }

  bool ValidateContent( vector<string> content ) {
    cout << "Checking file format...";
    bool valid = true;
    if(content.empty()){
      cout << NO_CONTENT << endl;
      valid = false;
    } else if (content.size() != VALID_FILE_SIZE) {
      cout << INVALID_SIZE << " file has #lines: " << content.size() << endl;
      valid = false;
    } else if (content[NAME].substr(0, 4).compare("NAME") != 0) {
      cout << INSUFICIENT_CONTENT << "NAME" << endl;
      valid = false;
    } else if (content[TYPE].substr(0, 4).compare("TYPE") != 0) {
      cout << INSUFICIENT_CONTENT << "TYPE" << endl;
      valid = false;
    } else if (content[CODIFICATION].substr(0, 12).compare("CODIFICATION") != 0) {
      cout << INSUFICIENT_CONTENT << "CODIFICATION" << endl;
      valid = false;
    } else if (content[WIDTH].substr(0, 5).compare("WIDTH") != 0) {
      cout << INSUFICIENT_CONTENT << "WIDTH" << endl;
      valid = false;
    } else if (content[HEIGHT].substr(0, 6).compare("HEIGHT") != 0) {
      cout << INSUFICIENT_CONTENT << "HEIGHT" << endl;
      valid = false;
    } else if (content[ALIAS].substr(0, 6).compare("ALIAS") != 0) {
      cout << INSUFICIENT_CONTENT << "ALIAS" << endl;
      valid = false;
    }
    cout << "Success!" << endl;
    return valid;
  }
} // namespace filerd
