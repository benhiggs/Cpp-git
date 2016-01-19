#include <iostream>
#include <vector>
#include "ReadWords.h"
#include "Writer.h"

using namespace std;

int main() {
    char psname[80];    //char[] for the playscript input
    char ssname[80];    //char[] for the searchscript name
    char outname[80];   //char[] for the output file name
    vector <string> strlist;    //holds the string list


    cout<<"Please enter a PlayScript file name including .txt:"<<endl;  //input for playscript
    cin.getline(psname, sizeof psname);

    cout<<"Please enter a SearchScript name including .txt:"<<endl; //input for searchscript name
    cin.getline(ssname, sizeof ssname);

    cout<<"Please enter a name for the output file including .txt:"<<endl; //input for output file name
    cin.getline(outname, sizeof outname);

    //create ReadWords and Writer objects for the input file names
    ReadWords playlist(psname);
    ReadWords searchlist(ssname);
    Writer output(outname);

    //adds playscript words to playlist vector
    while (playlist.isNextWord()) {
        string s=playlist.getNextWord();
        strlist.push_back(s);
    }
    playlist.close();   //close file
    

    //output file header for the output file.
    cout<<"Outputting results from searching "<<psname<<" for words from "<<ssname<<endl;
    output.writeString("Outputting results from searching "+string (psname)+" for words from "+string (ssname));
    output.writeEol();output.writeEol();
    

    //output input sizes from playscript
    cout<<"There were "<<strlist.size()<<" words in the text. "<<endl;
    output.writeString("There were ");
    output.writeInt(strlist.size());
    output.writeString(" words in the text. ");
    output.writeEol();output.writeEol();
    
    
    //loops through search terms and counts and outputs occurences.
    while (searchlist.isNextWord()) {
        string s=searchlist.getNextWord();
	int count = 0; //count for occurrences
	    
	for (int z=0;z<strlist.size();z++) {
	    string x = strlist[z];	        
	    if (x == s) {
		count++; //if strings are equal, output
	    }	    
	}
	if(count>0){
	    //output all information regarding occurrences both on console and output file
	    cout << "The word " << s << " occurs :" << count << " times." << endl;
	    output.writeString(("The word: ") + (s) + (" occurs "));
	    output.writeInt(count);
	    output.writeString(" times.");
	    output.writeEol();
	}
	else{
	    //output does not occur on console and output file
	    cout << "The word " << s << " does not occur." << endl;
	    output.writeString(("The word: ") + (s) + (" does not occur."));
	    output.writeEol(); 
	}
    }
    
    searchlist.close(); //close file
    output.close(); //close the file
    
    //this holds the output on the screen. This way you get a chance to examine it to check it against the output file
    cout<<"Please enter e to close the program once you have examined the outputs."<<endl;
    string s; cin>>s;
    
return 0;
}