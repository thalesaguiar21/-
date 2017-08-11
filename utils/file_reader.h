#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "image.h"

using std::cout;
using std::endl;

namespace utilities {
	// Reads a file with a given name and creates a Image object with its content.
	// This method also verify the file format, which must be for example:
	// ---------------------------------------------------------------------------
	// NAME = background.ppm
	// TYPE = PPM
	// CODIFICATION = binary   # COuld also be: ascii
	// WIDTH = 200
	// HEIGHT = 100
	// UPPER_LEFT = 0 255 0    # Superior left corner color (green)
	// LOWER_LEFT = 0 0 0      # Inferior left corner color (black)
	// UPPER_RIGHT = 255 255 0 # Superior right corner color (yellow) 
	// LOWER_LEFT = 255 0 0    # Inferior right corner color (red) 
	// ---------------------------------------------------------------------------

	std::vector<std::string> read_file(std::string file_name) {
		const int LINES = 9;
		std::vector<std::string> file_lines;

    	std::ifstream myfile(file_name);
    	cout << "Opening file '" << file_name << "'...\n" <<endl;
		if( myfile.is_open() ) {
			cout << "Checking file format...\n";
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