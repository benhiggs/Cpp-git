using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "Student.h"
#include <list>
#include <algorithm>

//allows the sort algorithm to sort the vector by regno
struct sortbyid{
    bool operator() (const Student& student1, const Student& student2){
        return (student1.getRegNo() < student2.getRegNo()); //smallest first ordering.
    }
};

//function that prints the students with marks higher than n.
int greaterPrint (vector<Student> students, float mark){
    sort(students.begin(),students.end(),sortbyid());   //sort list of student by regno

    int c = 0;                                                                      //loop count
    cout<<"\nListing students with a mark higher than "<<mark<<endl;                //title
    for(vector<Student>::iterator it = students.begin(); it!=students.end(); ++it){ //loop through students in vector
        if(it->returnMaxMark()>mark){                                               //if max mark is more than mark..
            cout<<*it<<endl;                                                        //output student details and increment count
            c++;
        }
    }
    if(c==0){      //if no students found output error.
        cout<<"There were no students found."<<mark<<endl;
    }
}


int greaterModulePrint(vector<Student> students, string module, float mark){
    sort(students.begin(),students.end(),sortbyid());   //sort list of student by regno
    cout<<"\nListing students with a mark higher than "<<mark<<" in module CE"<<module<<endl;
    int c = 0;                                                                      //loop count
    for(vector<Student>::iterator it = students.begin(); it!=students.end(); ++it){ //loop through students
        try{    //try to get mark for module
            float realmark = it->getMark("CE"+module);
            if(realmark>=mark){ //if mark is higher than arg.
                cout<< "Name:"<<it->getName()<<", Regno:" << it->getRegNo() << ", Module: CE"<<module<<", Mark: "<<realmark<<endl; //output details and increment count
                c++;
            }
        }
        catch(NoMarkException e){}  //catch exception but do nothing.
    }
    if(c==0){      //if no students found output error.
        cout<<"There were no students found."<<mark<<endl;
    }
}




int main()
{
    ifstream studs; //stream for studs file
    ifstream marks; //stream for marks file
    char studentfilename[80];    //char[] for the student input
    char marksfilename[80];    //char[] for the marks name
    vector <Student> studentlist;   //student vector
    list <string> modules;    //list of modules

    //get file name for studs and open it.
    cout<<"Please enter the student list file name including .txt:"<<endl;  //input for student list
    cin.getline(studentfilename, sizeof studentfilename);
    studs.open(studentfilename);

    //get file name for marks and open it
    cout<<"Please enter the mark list file name including .txt:"<<endl;  //input for student list
    cin.getline(marksfilename, sizeof marksfilename);
    marks.open(marksfilename);

    //check file errors.
    if (!studs){
        cout << "Failed to open " << studentfilename << endl;
        exit(1);
    }
    if (!marks){
        cout << "Failed to open " << marksfilename << endl;
        exit(1);
    }

    //get next input line from students
    char line [80];
    studs.getline(line,80);
    while(studs.good()){    //while there is a next line of input
        string l = (string)line;
        int id =atoi(l.substr(0,5).c_str());    //get regno from first 6 chars
        string name=l.substr(6,l.length()-6);   //get name from rest of file

        studentlist.push_back(Student(name,id));//add new student to vector of students

        studs.getline(line,80); //get next line
    }


    //Import student marks
    cout<<"Mark import:"<<endl;
    char line1[80];
    marks.getline(line1,80);//get line
    while(marks.good()){    //if there is a next line of input from file
        string l = (string)line1;
        int id =atoi(l.substr(0,5).c_str());    //get regno from first 6 chars
        string module=l.substr(6,5);            //get module from next 5
        double mark =atof(l.substr(12,4).c_str());  //get mark from remaining 4

        //find student in vector of students and add marks
        bool f = false;
        int c = 0;
        while (f== false){
            for(vector<Student>::iterator it = studentlist.begin(); it!=studentlist.end(); ++it){   //for all students
                if(it->getRegNo()==id){                                                             //if student id matches regno of mark line
                    it->addMark(module,(float)mark);                                                //add mark and exit loop
                    f=true;
                }
                else{                                                                               //else, go to next and increment counted students
                    c++;
                }
            }
            if(c==studentlist.size()){                                                              //if all students have been searched, output error.
                cout<<"Student wih id "<<id<<" not found"<<endl;
                f=true;
            }
        }
        modules.push_back(module);  //add module to list
        marks.getline(line1,80);
    }

    //sort list of modules
    modules.sort();
    modules.unique();

    //output all student results.
    cout<<endl<<"All student results:"<<endl;
    for (vector<Student>::const_iterator it = studentlist.begin(); it!=studentlist.end(); ++it){    //loop through all students and get regno
        int id = it->getRegNo();
        cout<<"Student: "<<id<<" Results: ";                                                        //output regno
        int markcount=0;                                                                            //count up marks

        for (list<string>::const_iterator it1 = modules.begin(); it1 !=modules.end(); ++it1) {      //for all modules
            float mark;
            try{                                                                                    //try to search for module (key) to mark pair in student map
                mark = it->getMark(*it1);
                cout<<*it1<<" "<<mark<<", ";                                                        //if mark exists, output mark and module name
                markcount++;
            }
            catch(NoMarkException){
            }
        }
        if(markcount==0){                                                                           //if no marks are found, output error msg
            cout<<"No Marks on system";
        }
        cout<<"\n";
    }



    //menu output
    bool l = true;  //menu loop
    char choice[2]; //choice input

    while (l==true){//while loop:
        cout<<"\n\nTest function loop:\nYour options are:\n1 - Print students with grades greater than N.\n2 - Print students with grades greater than N in module X\n3 - Exit\nMake your choice now...";
        cin.getline(choice, sizeof choice); //get input

        if(atof(choice) == 1){                                  //if choice is 1
            char mark[5];
            cout<<"\nEnter the mark you wish to filter by: ";
            cin.getline(mark, sizeof mark);                     //get mark
            float m =(float) atof(mark);

            greaterPrint(studentlist,m);                        //print student details with marks higher than m
        }
        else if(atof(choice) == 2){                                     //if choice is 2
            char mark[5];
            char mod[5];
            cout<<"\nEnter the module number you wish to filter by: ";
            cin.getline(mod, sizeof mod);                               //get module number
            cout<<"\nEnter the mark you wish to filter by: ";
            cin.getline(mark, sizeof mark);                             //get mark
            float m =(float) atof(mark);

            greaterModulePrint(studentlist,mod,m);                      //print student details with marks higher than m in mod
        }
        else if(atof(choice) == 3){     //if choice is 3, exit
            l=false;
        }
        else{   //output error.
            cout<<"\nYou did not enter a correct choice. Please choose between 1,2,3.\n";
        }
    }
}
