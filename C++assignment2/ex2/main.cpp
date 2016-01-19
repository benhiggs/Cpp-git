#include <iostream>
#include <map>          //to store words
#include "UpperFilter.h"
#include "ValidFilter.h"
#include "VowelFilter.h"
#include <vector>       //to store sorted map
#include <algorithm>    //sort


using namespace std;

//used with sort function on a vector of pairs by the count. The vector is a dump of the word map. This is sorted for output.
struct sortbyoccurences {
    bool operator()(const pair<string, int> pair1, pair<string, int> pair2) {
        return (pair1.second > pair2.second); //return t/f based on the comparison between pair1 and 2. > comparison is descending.
    }
};

//define readwords out of main so that is it reachable and can be initialised. This is a pointer.
ReadWords *wordfile;

int main() {
    char filename[80];  //filename input char array
    map<string,int> words;  //map of words
    int i;  //input for filter choice

    //get filename
    cout<<"Please enter the word file name including .txt:"<<endl;
    cin.getline(filename, sizeof filename);

    //output filter options and get input
    cout<<"\nPlease enter the filter you wish to choose:"<<endl;
    cout<<"1 - Upper case filter.   Word must have at least one uppercase letter"<<endl;
    cout<<"2 - Vowel filter.   Word must have at least three vowels"<<endl;
    cout<<"3 - Non empty filter.   Word must have at least one letter and one punctuation character"<<endl;
    cout<<"\nPlease select the correspoding number"<<endl;
    cin>>i;

    if(i==1){
        wordfile = new UpperFilter(filename);   //set UpperFilter. gets strings with an uppercase char
    }
    else if(i==2){
        wordfile = new VowelFilter(filename);   //set VowelFilter. gets strings with three or more vowels
    }
    else if(i==3){
        wordfile = new ValidFilter(filename);   //set ValidFilter. gets strings with at least one punct and letter       
    }
    else{exit(0);}  //exits if incorrect choice made


    //while there is a next word, get it.
    while(wordfile->isNextWord()){
        string word = wordfile->getNextFilteredWord();
        if(word!=""){
            //check for occurences. if there are, add one to the map value
            if(words.count(word)>0){
                words[word]+=1;
            }
            //otherwise, add a new map pair.
            else{
                words.insert(pair<string,int>(word,1));
            }
        }
    }


    //copy map into a vector for sorting and output.
    vector <pair<string,int> > mapcopy; //copy of the map in a vector of pairs.
    //add to vector
    for( map<string,int>::iterator it = words.begin(); it != words.end(); ++it ) {
        mapcopy.push_back( *it );
    }
    //sort map using sortbyoccurences to descending order.
    sort(mapcopy.begin(),mapcopy.end(),sortbyoccurences());

    //output word map stats.
    cout<<"\nFile has been processed..\n\nWord map is "<<words.size()<<" words long.\n\nThis filter will show the top 10 or 10% (whatever is least) from the map.\n"<<endl;

    //get 10% of map size. This allows the output to print 10 or 10% of the map, depending on the size.
    int r=10;
    if(mapcopy.size()*0.1<10){
        if(mapcopy.size()*0.1<=0){  //make sure there is always an output.
            r=1;
        }
        else {
            r = mapcopy.size() * 0.1;
        }
    }

    //output loop. This outputs the words and occurences.
    int c = 0;
    for(vector<pair<string,int> >::const_iterator it = mapcopy.begin(); it != mapcopy.end(); it++){
        if(c==0){//first highest word output.
            cout<<"Top portion of list is:\nWord: "<<it->first<<", Occurences: "<<it->second<<endl;
        }
        else if(c<r){
            cout<<"Word: "<<it->first<<", Occurences: "<<it->second<<endl;
        }
        else if(c==(mapcopy.size()-r)){//first lowest word output.
            cout<<"\nBottom portion of list is:\nWord: "<<it->first<<", Occurences: "<<it->second<<endl;
        }
        else if(c>(mapcopy.size()-r)){
            cout<<"Word: "<<it->first<<", Occurences: "<<it->second<<endl;
        }
        c++;
    }
    //output other words part.
    cout<<"\nThere are "<<mapcopy.size()-2*r<<" words between the top and bottom sections in the sorted map.";
system("pause");
    return 0;
    
}