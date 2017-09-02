#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

namespace utility 
{
	// Reads a file with a given name and creates a Image object with its content.
	vector<string> read_file(string file_name) 
	{
		vector<string> file_lines;

		std::ifstream myfile(file_name);
		cout << "Opening file '" << file_name << "'...\n";
		
		if( myfile.is_open() ) {
			string line;
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