using namespace std;

#include <iostream>
#include <iomanip>
#include "Time.h"

Time::Time()
{ hour = min = sec = 0;
}

Time::Time(int h, int m, int s)
{ setTime(h, m, s);
}

void Time::setTime(int h, int m, int s)
{ hour = (h>=0 && h<24) ? h : 0;
    min = (m>=0 && m<60) ? m : 0;
    sec = (s>=0 && s<60) ? s : 0;
}

Time& Time::operator+=(unsigned int n)
{ sec += n;
    if (sec >= 60)
    { min += sec/60;
        sec %= 60;
        if (min >=60)
        { hour = (hour + min/60) % 24;
            min %= 60;
        }
    }
    return *this;
}

Time Time::operator+(unsigned int n) const
{ Time tCopy(*this);
    tCopy += n;
    return tCopy;
}

Time& Time::operator++()        // prefix version
{ *this += 1;
    return *this;
}

Time Time::operator++(int n)    // postfix version
{ Time tCopy(*this);
    *this += 1;
    return tCopy;
}


// new member functions

//-= to operator, works out the time from the int n given (seconds) and minuses it from the time object
Time& Time::operator-=(unsigned int n)
{ int h = n/3600;           //working out hours, mins and seconds using modulus
    int m = (n%3600)/60;
    int s = (n%3600)%60;

    sec -=s;        //minus the new times from the objects time variables.
    min -=m;
    hour -=h;

    if (sec<0){sec=60+sec;min--;}       //when you go into negative seconds, take a min, when you go into negative mins, take an hour.... so on
    if (min<0){min=60+min;hour--;}
    if (hour<0){hour=0;min=0;sec=0;}    //when you go into -hours, time left is 0:0:0

    return *this;
}

//- operator, works out the time from given seconds and minuses it from time object
Time Time::operator-(unsigned int n) const
{ Time tCopy(*this);    //copies object
    tCopy -= n;         //uses above method
    return tCopy;
}

//== operator, works out if the time given is equal to the time object
bool Time::operator==(const Time& t) const
{  if (this->hour == t.hour){
        if (this->min == t.min){
            if (this->sec == t.sec){
                return true;                //if all elements are equal, then times are equal.
            }
        }
    }
    else{
        return false;    //otherwise its false.
    }
}

//= operator, works out if the times are not equal
bool Time::operator!=(const Time& t) const
{ if (t==*this){  //uses the == operator defined above
        return false;
    }
    else{
        return true;
    }
}

//< operator, works out if the time object is smaller than the supplied time arguement
bool Time::operator<(const Time& t) const
{ int a = (this->hour*60 + this->min*60 + this->sec);   //works out times in seconds
    int b = (t.hour*60 + t.min*60 + t.sec);
    if (a<b){return true;} //compares seconds
    return false;
}

//<= operator,if this is equal or is smaller than, return true. else return false
bool Time::operator<=(const Time& t) const
{ if (t==*this || *this<t){
        return true;
    }
    else{
        return false;
    }
}



ostream& operator<<(ostream &o, const Time &t)
{ o << setfill('0') << setw(2) <<  t.hour << ':' << setw(2) << t.min << ':' << setw(2) << t.sec;
    return o;
}

//new friend functions

//-- operator. prefix version. decrements time by one sec, then returns new time
Time &operator--(Time &time1)
{ time1.operator-=(1);
    return time1;
}

//-- operator. postfix version. decrements time by one sec, then returns the old time.
Time operator--(Time &time1, int i) {
    Time tCopy = time1;
    time1.operator-=(1);
    return tCopy;
}

//> operator. compares two times, if time1 is larger than time2 return true
bool operator>(const Time &time1, const Time &time2) {
    if (!time1.operator<=(time2)){return true;}//uses the <= operator and negates the answer.
    else {return false;}
}

//>= operator. compares two times, if time1 is bigger or equal to time 2 return true.
bool operator>=(const Time &time1, const Time &time2) {
    if (!time1.operator<(time2)){return true;} //uses the < operator and negates the answer.
    else {return false;}
}

//- operator. returns the difference in mins, between two times.
unsigned int operator-(const Time &time1, const Time &time2) {
	int dif=0;
	int sd=0;
	int md=0;
	int hd=0;
	
	if (time2<=time1){ //if the start is before the finish, work out normally
	sd = time1.sec - time2.sec;
	md = time1.min - time2.min;
	hd = time1.hour - time2.hour;
	}
	
	else{ //if the start is after the finish, the start time is the day before, and the difference is worked out.
	sd = time1.sec - time2.sec;
	md = time1.min - time2.min;
	hd = 24 - time2.hour + time1.hour ; //minus the times from a full day to work out real difference.
	}

    if(sd!=0){ if(sd<0){md--;} else{md++;} } // works out difference in seconds and adds or removes based on the negativity of the seconds.

    dif =(hd* 60)+md; //works out the mins

    return (unsigned int) dif; //cast to unsigned int and return
}
