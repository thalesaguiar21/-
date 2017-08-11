#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <iostream>
#include <vector>
#include <string>

#include "vec3.h"

namespace utility {

	class Image {

		public:
			// == Image and file constants
			// Error messages
			const std::string NO_CONTENT          = "[ERROR] No content given!";
			const std::string INVALID_SIZE        = "[ERROR] Insuficient information, or file is too big!";
			const std::string INSUFICIENT_CONTENT = "[ERROR] No information given: ";
			// Valid file attributes
			const char COMMENT_CHAR   = '#';
			const int VALID_FILE_SIZE = 9;
			// Atributes position
			enum attr_position { NAME, TYPE, CODIFICATION, WIDTH, HEIGHT, UPPER_LEFT, LOWER_LEFT, UPPER_RIGHT, LOWER_RIGHT };

			std::string name;
			std::string type;
			std::string codification;
			int width;
			int height;
			rgb upper_left;
			rgb lower_left;
			rgb upper_rigth;
			rgb lower_right;

			inline void from(std::vector<std::string> content) {

				if (validate_content(content)) {
					std::vector<std::string> tmp_content = remove_comments(content);
					name = tmp_content[NAME].substr(7, tmp_content[NAME].length());
					type = tmp_content[TYPE].substr(7, tmp_content[TYPE].length());

					codification = tmp_content[CODIFICATION].substr(15, tmp_content[CODIFICATION].length());
					width = std::stoi(tmp_content[WIDTH].substr(8, tmp_content[WIDTH].length()), nullptr);
					height = std::stoi(tmp_content[HEIGHT].substr(9, tmp_content[HEIGHT].length()), nullptr);


					std::cout << name <<std::endl;
					std::cout << type <<std::endl;
					std::cout << codification <<std::endl;
					std::cout << width <<std::endl;
					std::cout << height <<std::endl;
				}
			}

			private:
				// Remove any strings after a COMMENT_CHAR
				inline std::vector<std::string> remove_comments(std::vector<std::string> content) {
					for (int i = 0; i < content.size(); ++i)
					{
						int comment_pos = content[i].find_first_of(COMMENT_CHAR);
						content[i] = content[i].substr(0, comment_pos);
					}

					return content;
				}

				// Verify if the given file content match the standard format
				inline bool validate_content(std::vector<std::string> content){

					std::cout << "Checking file format...\n";
					bool valid = true;
					if(content.empty()){
						std::cout << NO_CONTENT <<std::endl;
						valid = false;
					} else if (content.size() != VALID_FILE_SIZE) {
						std::cout << INVALID_SIZE << " file has #lines: " << content.size() <<std::endl;
						valid = false;
					} else if (content[NAME].substr(0, 4).compare("NAME") != 0) {
						std::cout << INSUFICIENT_CONTENT << "NAME" <<std::endl;
						valid = false;
					} else if (content[TYPE].substr(0, 4).compare("TYPE") != 0) {
						std::cout << INSUFICIENT_CONTENT << "TYPE" <<std::endl;
						valid = false;						
					} else if (content[CODIFICATION].substr(0, 12).compare("CODIFICATION") != 0) {
						std::cout << INSUFICIENT_CONTENT << "CODIFICATION" <<std::endl;
						valid = false;						
					} else if (content[WIDTH].substr(0, 5).compare("WIDTH") != 0) {
						std::cout << INSUFICIENT_CONTENT << "WIDTH" <<std::endl;
						valid = false;						
					} else if (content[HEIGHT].substr(0, 6).compare("HEIGHT") != 0) {
						std::cout << INSUFICIENT_CONTENT << "HEIGHT" <<std::endl;
						valid = false;						
					} else if (content[UPPER_LEFT].substr(0, 10).compare("UPPER_LEFT") != 0) {
						std::cout << INSUFICIENT_CONTENT << "UPPER_LEFT" <<std::endl;
						valid = false;						
					} else if (content[LOWER_LEFT].substr(0, 10).compare("LOWER_LEFT") != 0) {
						std::cout << INSUFICIENT_CONTENT << "LOWER_LEFT" <<std::endl;
						valid = false;						
					} else if (content[UPPER_RIGHT].substr(0, 11).compare("UPPER_RIGHT") != 0) {
						std::cout << INSUFICIENT_CONTENT << "UPPER_RIGHT" <<std::endl;
						valid = false;						
					} else if (content[LOWER_RIGHT].substr(0, 11).compare("LOWER_RIGHT") != 0) {
						std::cout << INSUFICIENT_CONTENT << "LOWER_RIGHT" <<std::endl;
						valid = false;						
					}
					return valid;
				}
	};
}

#endif