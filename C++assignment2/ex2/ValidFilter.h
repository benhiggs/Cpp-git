//
// Created by benhi on 10/01/2016.
//

#ifndef EX2_VALIDFILTER_H
#define EX2_VALIDFILTER_H

#include "ReadWords.h"

//class for ValidFilter, a derived class of ReadWords.
class ValidFilter : public ReadWords{
public:
    ValidFilter(const string &file);
    //virtual filter funct.
    virtual bool filter(string s);

};


#endif //EX2_VALIDFILTER_H
