#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>

namespace utilities {
	class Image {
		public:
			std::string name;
			std::string format;
			std::string codification;
			std::string content;
			int width;
			int height;
	};
}

#endif