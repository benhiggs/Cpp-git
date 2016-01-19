//
// Created by benhi on 10/01/2016.
//

#include "ValidFilter.h"

//constructor. Allows the construction of the derived filter and the base.
ValidFilter::ValidFilter(const string &file) :ReadWords(file){}

//virtual filter function
bool ValidFilter::filter(string s) {
    int punctcount = 0;                         //punctuation count
    int lettercount = 0;                        //letter count

    for (int x = 0; x < s.size(); x++) {        //loop through word
        if (ispunct(s[x])) {                    //if char is punctuation, increment punctuation count
            punctcount++;
        }
        else if(s[x]!=' ' && !isdigit(s[x])){   //if char is a letter, increment letter count
            lettercount++;
        }

        if(punctcount !=0 && lettercount!=0){   //if there is at least one letter and punctuation, return true
            return true;
        }
    }
    return false;                               //if not more than one letter and punctuation, return false
}
