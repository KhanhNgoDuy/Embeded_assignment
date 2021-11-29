#include <fstream>
#include <string>
#include "translator.cpp"

using namespace std;

int trchar = 0;     //Counter for translated characters.
int errchar = 0;   //Counter for error characters.

int err_textF(const char *inp) {
 
    fstream myFile;
    string line, s = "";
    int line_counter = 0;

    myFile.open(inp, ios::in);
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            line_counter ++;
            for (int i = 0; i < line.length(); i++) {
                line[i] = tolower(line[i]);
                s += line[i];

                if (line[i] != ' ' && line[i] != '\n') {
                    for (int j = 0; j < size_of_array; j++) {
                        if (s == letter[j]) {
                            j = size_of_array;
                            trchar++;
                        }
                        else if (j == (size_of_array - 1)) {
                            cout<<"Error AB: Unrecognize character "<<line[i]<<" on line "<<line_counter<<"\n";
                            errchar++;
                            
                        };
                    };
                };
                s = "";
            };
        };

        myFile.close();
    };
};

int err_morse(const char *inp) {
    fstream myFile;
    string line, s_temp = "";
    int line_counter = 0, space_counter = 0, err_morse = 0, j = 0;

    myFile.open(inp, ios::in);
    if (myFile.is_open()) {
        while (getline(myFile, line)) {

            line_counter++;
            
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '.' || line[i] == '-') {
                    s_temp += line[i];
                    space_counter = 0;
                }
                else if (line[i] == '/' || line[i] == ' ' || line[i] == '\n') {
                    if (line[i] == ' ') {
                        space_counter++;
                        if (space_counter == 2) {
                            cout<<"Error 01: Extra blankspace on line "<<line_counter<<"\n";
                            err_morse++;
                            space_counter = 0; 
                        };
                    }
                    else if (line[i] == '/') {
                        space_counter = 0;
                    };

                    for (int j = 0; j < size_of_array; j++) {
                        if (s_temp.length() > 7) {
                            cout<<"Error 02: Invalid Morse code "<<s_temp<<" on line "<<line_counter<<"\n";
                            err_morse++;
                            s_temp = "";
                            j = size_of_array;
                        }

                        else if (s_temp != morse[j] && j == (size_of_array - 1) ) {
                                cout<< "Error 03: Invalid Morse code "<<s_temp<<" on line "<<line_counter<<"\n";
                                err_morse++;
                                s_temp = "";
                        }
                    
                        else if (s_temp == morse[j] || s_temp == "") {
                            s_temp = "";
                            j = size_of_array;
                        };
                    };
                };
            };
            s_temp = "";
        };
        myFile.close();
    };
    return err_morse;
};

// int main(){

//     const char* inp = "input.txt";

//     err_textF(inp);
//     cout<<"Char counter: "<<trchar<<"\nError counter: "<<errchar; 
// }