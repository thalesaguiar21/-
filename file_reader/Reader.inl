#include "Reader.h"

namespace filerd {

  bool ReadFile( string file_name, vector<string> &content) {
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

  void WriteOnFile(Image img) {
    cout << "\nWriting result into " << img.name << "... ";
    std::ofstream file("imgs/" + img.name);
    file << img.Header();
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
