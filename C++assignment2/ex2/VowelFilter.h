//
// Created by benhi on 10/01/2016.
//

#ifndef EX2_VOWELFILTER_H
#define EX2_VOWELFILTER_H

#include "ReadWords.h"

//class for UpperFilter, a derived class of ReadWords.
class VowelFilter : public ReadWords{
public:
    VowelFilter(const string &file);
    //virtual filter funct.
    virtual bool filter(string s);

};

#endif //EX2_VOWELFILTER_H
