#include "Reader.h"

namespace filerd {

  bool ReadFile( string file_name, vector<string> content) {
    bool hasErros = false;
    cout << "Opening file...";
    std::ifstream myfile(file_name);
    if( myfile.is_open() ) {
      cout << "Success!" << endl;

      cout << "Reading file... ";
      string line;
      while( getline(myfile, line) ) {
        content.push_back(line);
      }
      cout << "Done!" << endl;
    } else {
      cout << "[ERROR] Could not open the file \"" << file_name << "\"" << endl;
      hasErros = true;
    }
    myfile.close();
    return hasErros;
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
    } else if (content[ALIAS].substr(0, 5).compare("ALIAS") != 0) {
      cout << INSUFICIENT_CONTENT << "ALIAS" << endl;
      valid = false;
    }
    cout << "Success!" << endl;
    return valid;
  }

  void WriteOnFile(Image img) {
    cout << "\nWriting result into " << img.name << "... ";
    std::ofstream file("../" + img.name);
    file << img.Header();
    int a;
    for(auto lin=img.height-1; lin >= 0; lin--) {
      for (auto col = 0; col < 3*img.width; col++) {
        file << img.content[lin][col];
        string tmp = ((col+1) % 3 == 0) ? ("\n") : (" ");
        file << tmp;
      }
    }
    file.close();
    cout << "Done!" << endl;
  }
} // namespace filerd
