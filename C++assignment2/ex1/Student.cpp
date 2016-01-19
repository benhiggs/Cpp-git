//
// Created by ben higgs .
//
using namespace std;
#include <iostream>
#include "Student.h"
#include <algorithm>


Student::Student(const string &name, int regNo) : Person(name){
    map <string,float> marks;
    this->regNo = regNo;
}

int Student::getRegNo() const{
    return regNo;
}

void Student::addMark(const string &module, float mark) {
    if(marks.count(module)==0){
        marks.insert ( pair<string,float>(module,mark) );
    }
    else{
        marks.erase(module);
        marks.insert ( pair<string,float>(module,mark) );
    }

}

float Student::getMark(const string &module) const throw (NoMarkException){
    map<string,float>::const_iterator it;
    it = marks.find(module);
    if(it != marks.end())
    {
        return it->second;
    }
    else{
        throw NoMarkException();
        }
}

//public function to return the value from the private function getMaxMark()
float Student::returnMaxMark() const {
    return getMaxMark();
}


//privates

//replace << operator for Student
ostream& operator<<(ostream &str, const Student &s){
    if(s.marks.empty()){    //if no marks are in the map
        return str << "Name: " << s.name << ", Regno:" << s.getRegNo() << ", No Marks";    //student has no marks.
    }
    else{   //else
        return  str << "Name: " << s.name << ", Regno:" << s.getRegNo() << ", Minumum:" << s.getMinMark() << ", Maximum:" << s.getMaxMark() << " Average:" << s.getAverageMark();   //use min, max and average mark functions
    }
}

//get average mark for student
float Student::getAverageMark() const {
    float m = 0.0;  //total marks
    int c = 0;      //mark count
    for(map<string,float>::const_iterator it = marks.begin(); it != marks.end(); it++) {    //loop through marks in map
        m = m+it->second;       //add all marks
        c++;                    //increment count
    }
    return (m/c);   //return average
}

//get max mark for student
float Student::getMaxMark() const{
    float m = 0.0;      //max mark = 0.
    for(map<string,float>::const_iterator it = marks.begin(); it != marks.end(); it++) {    //loop through marks in map
        if(m<it->second){   //if current is larger than m
            m=it->second;   //replace m with current mark
        }
    }
    return (m); //return max
}

//get min mark for student
float Student::getMinMark() const{
    float m = 100.0;    //min mark =100.
    for(map<string,float>::const_iterator it = marks.begin(); it != marks.end(); it++) {    //loop through marks in map
        if(m>it->second){   //if current is smaller than m
            m=it->second;   //replace m with current mark
        }
    }
    return (m); //return min
}


