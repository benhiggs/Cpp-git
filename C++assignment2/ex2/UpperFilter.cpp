//
// Created by benhi on 10/01/2016.
//

#include <string.h>
#include "UpperFilter.h"

//constructor. Allows the construction of the derived filter and the base.
UpperFilter::UpperFilter(const string &file) : ReadWords(file) {}

//virtual filter function
bool UpperFilter::filter(string s) {
    for (int x = 0; x < s.size(); x++) {    //loop through characters
        if (isupper(s[x])) {                //if character is upper case:
            return true;                    //return true, as work must contain at least one upper case char
        }
    }
    return false;                           //if no uppercase is found, return false
}
