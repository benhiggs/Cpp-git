//
// Created by benhi on 10/01/2016.
//

#include <string.h>
#include "VowelFilter.h"

//constructor. Allows the construction of the derived filter and the base.
VowelFilter::VowelFilter(const string &file):ReadWords(file) {}

//virtual filter function
bool VowelFilter::filter(string s) {
    int count = 0;                                  //vowel count
    for (int x = 0; x < s.size(); x++) {            //loop through each char
        if (strchr("AEIOU",toupper(s[x]))!=NULL) {  //if char is either A,E,I,O,U, increment count
            count++;
        }
    }

    if(count==3){       //if count is at least three, return true
        return true;
    }
    else{               //otherwise, return false.
        return false;
    }
}
