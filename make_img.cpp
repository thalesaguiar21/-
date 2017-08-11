#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "utils/file_reader.h"
#include "utils/image.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using utility::Image;

int main(int argc, char *argv[] ) {

    if(argc < 2){
        cout << "Plase, give a filname as parameter!\n";
    } else if (argc > 2) {
        cout << "The program only takes one argument!\n";
    } else {
        int l = 0;
        std::vector<string> content = utility::read_file(argv[1]);
        Image img;
        img.from(content);
        std::ofstream imgFile("../imgs/" + img.name);

        imgFile << "P3" << "\n";
        imgFile << img.width << " " << img.height << "\n";
        imgFile << "255\n";

        int r = 255;
        int g = 255;
        int b = 0;

        double tgcol = 255.0 / (img.width - 1);
        double tglin = 255.0 / (img.height - 1);

        cout << "Rendering image...";
        for(int i=0; i < img.height; i++) {
            for(int j=0; j < img.width; j++) {

                r = j * tgcol;
                imgFile << r << " " << g << " " << b << "\n";
            }
            g = 255 - i * tglin;
        }
        cout << "Success!\n";
    }
    return 0;
}