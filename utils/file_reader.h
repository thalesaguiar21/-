#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

namespace utility {
	// Reads a file with a given name and creates a Image object with its content.

	std::vector<std::string> read_file(std::string file_name) {
		std::vector<std::string> file_lines;

    	std::ifstream myfile(file_name);
    	cout << "Opening file '" << file_name << "'...\n";
		if( myfile.is_open() ) {
			std::string line;
			// Extract the content of the given file, 
			while( getline(myfile, line) ) {

				file_lines.push_back(line);
			}
		} else {
			cout << "[ERROR] Could not open the file " << file_name <<endl;
		}

		myfile.close();
		return file_lines;
	};
}

#endif