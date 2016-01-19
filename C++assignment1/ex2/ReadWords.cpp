//
// Created by benhi on 12/11/2015.
//

#include "ReadWords.h"
#include <fstream>
#include <iostream>
#include <cstdlib>


//opens the file for reading
ReadWords::ReadWords(const char *filename) {
    wordfile.open(filename); //wordfile is now the object file
    eoffound=false; //sets ed of file to false
    if (!wordfile){
        cout << "Failed to open " << filename << endl;
        exit(1);
    }
}

//closes the file
void ReadWords::close() {
wordfile.close();
}

//gets the next word for reading character by character.
string ReadWords::getNextWord() {

    char c;	//this is the character being read in
    string s;	//this is the string being constructed and passed back
    bool endloop = false;	//looping boolean valuye to control while loops
    
    //while end of file is not found and whilst end of loop is false.When this exits, a string will have been constructed.
    while (!wordfile.eof() && !endloop){
    
    	//checks if nextword holds a character for the start of the next word. if not, then c is the next character from the wordfile. (this should only work for the first character of each word.)
    	if(s.length()<1){
            if(nextword.length()==1){c= (char) nextword.at(0);nextword.erase(0,1);}
            else{c = (char) wordfile.get();}
        }
        else{c = (char) wordfile.get();}
        
        //checks characters are valid. 
        if (isspace(c)&&(s.length()>=1)){endloop=true;} //<<<<<<DO I NEED TO NOT INCLUDE NUMBERS>>>>>
        else if (isspace(c) || !isalpha(c)){}
        else{s.append(1,tolower(c));} //add to string.
    }
    
    //trims whitespace off the ed of the string.
    for (int i = (s.length()-1);i>0;i--){
        if(ispunct(s.at(s.length()-1))){s.erase(i);}
    }
    
    //control for second loop that holds the start of the next word.
    endloop = false;
    
    //stores the next character from the start of the next word as the nextword variable.
    while (!endloop && !wordfile.eof()){
            c = (char) wordfile.get();
            if (isspace(c) || ispunct(c) ){}
            else{nextword=c;endloop=true;}
    }
    
    //if end of file has been found, set eof to true
    if(wordfile.eof()){eoffound=true;}      

    return s;	//return string    
}

//is next word checks the eoffoudn variable, returns true is it has not been found, and false otherwise.
bool ReadWords::isNextWord() {
    return !eoffound;
}

