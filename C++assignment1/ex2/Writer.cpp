//
// Created by benhi on 12/11/2015.
//

#include <cstdlib>
#include "Writer.h"

//opens file, or creates a new one if needed.
Writer::Writer(const char *filename) {
    out.open(filename); //file object
    if (!out){
        cout<<"Cannot output to "<<filename<<endl;
        exit(1);
    }
}

//outputs an integer to the file
void Writer::writeInt(int n) {
    out<< n;
}

//outputs a character to the file
void Writer::writeChar(char s) {
    out<<s;
}

//outputs a string to the file
void Writer::writeString(string s) {
    out<<s;
}

//outputs a new line character to the file
void Writer::writeEol() {
    out<<endl;
}

//closes the file
void Writer::close() {
    out.close();
}
