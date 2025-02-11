#include <stdio.h>
#include <string>
#include <iostream>
#define size_of_array 51

using namespace std;

string letter[size_of_array] = {"a", "b", "c", "d", "e", "é", "f", "g", "h", "i", "j",  //11 - 1
                "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",                       //10 - 2
                "u", "v", "w", "x", "y", "z",                                           //6  - 3
                "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",                       //10 - 4
                ".", ",", ":", "?", "'",                                                //5  - 5
                "-", "/", "(", ")", "\"",                                               //5  - 6
                "=", "+", "×", "@"};                                                    //4  - 7

string morse[size_of_array] = {".-", "-...", "-.-.", "-..", ".", "..-..", "..-.", "--.", "....", "..", ".---",              //11 - 1
                                "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",                        //10 - 2
                                "..-", "...-", ".--", "-..-", "-.--", "--..",                                               //6  - 3
                                ".----", "..---", "...--", "....-", ".....","-....", "--...", "---..", "----.", "-----",    //10 - 4
                                ".-.-.-", "--..--", "---...", "..--..", ".----.",                                           //5  - 5                         
                                "-....-", "-..-.", "-.--.", "-.--.-", ".-..-.",                                             //5  - 6
                                "-...-", ".-.-.", "-..-", ".--.-."};                                                        //4  - 7

string letter_to_morse(string s) {      //Encrypting function

    string s_res = "";      //resulted string
    string s_temp = "";     //string used to compare

    //Modify the input string to lowercase
    for (int i = 0; i < s.length(); i++) 
        s[i] = tolower(s[i]);
    
    //Encrypt letter to morse code
    for (int i = 0; i < s.length(); i++) {
        s_temp += s[i];
        if (s[i] != ' ' && s[i] != '\n'){
            for (int j = 0; j < size_of_array; j++) {     //Scan through the "letter" array
                if (s_temp == letter[j])        //If the digit is valid, add the equivalent morse
                    s_res += morse[j] + ' ';    //code to the string, seperated by a blankspace
            };
        } 

        else if (s[i] == ' ')   //Seperate each
            s_res += "/ ";       //word by a '/'
        else if (s[i] == '\n') {
            s_res += '\n';
        }
        s_temp = "";      //Reset s_temp for new loop;
    };

    return s_res;
};

string morse_to_letter(string s) {      //Decrypting function
    // string s = ".- -...\n";
    string s_res = "";
    string s_temp = "";
    int counter = 0;        //Counter of blankspace ' '.

    //Modify the input string
    s += ' ';   

    //Decrypt Morse code to letter
    for (int i = 0; i < s.length(); i++) {      
        if (s[i] == '.' || s[i] == '-') {       
            s_temp += s[i];                     
            counter = 0;       
        }

        else if (s[i] == '\n' || s[i] == '/' || s[i] == ' ') {
            for (int j = 0; j < size_of_array; j++) {  
                if (s_temp.length() > 7) {          //Incorrect format
                    s_res += '#';                   //morse code is
                    s_temp = "";                    //decrypted as '#'.
                    j = size_of_array;
                }

                else if (s_temp == "")
                {
                    j = size_of_array;     
                }

                else if (s_temp == morse[j]) {      //Correct decryption            
                    s_res += letter[j];             
                    s_temp = "";        
                    j = size_of_array;
                }

                else if (j == (size_of_array-1)) {      //Unrecognized morse
                    s_res += '*';                       //code is
                    s_temp = "";                        //decrypted as '*'
                };
            };
            switch (s[i])
            {
                case '\n': 
                {
                    s_res += '\n';      
                    break;
                }
                case '/': 
                {
                    counter = 0;
                    s_res += ' ';
                    break;
                }
                case ' ':
                {
                    counter++;
                    break;
                }
            }
        }

        if (counter == 2) {      //For any extra ' ', 
            s_res += '$';        //a '$' character
            counter = 1;         //is added to s_res.
        };
    };

    s_res.resize(s_res.length() - 1);
    return s_res;
}

// int main(){         //Drive code
//     string s1 = ".-- .... .- - / .... .- - .... / --. --- -.. / .-- .-. --- ..- --. .... -";
//     string s_res1 = morse_to_letter(s1);
//     cout<<s_res1;
// }