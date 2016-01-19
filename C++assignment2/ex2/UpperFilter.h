//
// Created by benhi on 10/01/2016.
//

#ifndef EX2_UPPERFILTER_H
#define EX2_UPPERFILTER_H

#include "ReadWords.h"

//class for UpperFilter, a derived class of ReadWords.
class UpperFilter : public ReadWords {
public:
    UpperFilter(const string &file);
    //virtual filter funct.
    virtual bool filter(string s);

};

#endif //EX2_UPPERFILTER_H
