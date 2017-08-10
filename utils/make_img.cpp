#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::cin;


bool check_file(char *args[]) {
    std::ifstream myfile(args[1]);
    bool result = false;
    cout << "Opening " << args[1] << "...";
    if(myfile.is_open()){
        cout << "Sucess!\n";
        cout <<  "Cheking format of " << args[1] << "...";
        if(true) {
            cout << "Sucess\n";
            myfile.close(); 
            result = true;
        } else {
            cout << "[ERROR] Invalid file format!\n";
        }
    } else {
        cout << "[ERROR] Could not open file!\n";
    }
    return result;
}

int main(int argc, char *argv[] ) {

    if(argc < 2){
        cout << "Plase, give a filname as parameter!\n";
    } else if (argc > 2) {
        cout << "The program only takes one argument!\n";
    } else {
        int l = 0;
        if(check_file(argv)){

            char *content;

            int lin = 100;
            int col = 200;
            char content;
            while(myfile.get(content)){
                cout << content;
            }

            //myfile << get
            //myfile << col << " " << lin << "\n";
            //myfile << "255\n";

            int r = 0;
            int g = 0;
            int b = 0;

            double tgr = 255.0 / (lin - 1);
            double tgg = 255.0 / (col - 1);

            for(int i=0; i < lin; i++) {
                g = 255;
                for(int j=0; j < col; j++) {

                    g = j * tgg;
                    //myfile << r << " " << g << " " << b << "\n";
                }
                r = i * tgr;
            }
        }
    }
    return 0;
}