#include <iostream>
#include <string>
#include "date.h"
#include <ctime>
using namespace std;

int today(){

    // current date/time based on current system
    time_t now = time(0);

    tm *ltm = localtime(&now);
    
    string date="";
    date+=to_string(ltm->tm_mday )+"/";
    date+=to_string(1 + ltm->tm_mon)+"/";
    date+=to_string(1900 + ltm->tm_year);
    return(dateToInt(date));

}

bool inThePast(string date){
    int todayInt = today();
    if((dateToInt(date)-todayInt)<0) return true;
    else return false;
}

bool isDateFormatOk(string date){
    
    if(date.size()!=10) return false;
    for(int i=0;i<10;i++){
        if(i==2||i==5){
            if(date[i]!='/') return false;
        }else{
            if(!isdigit(date[i])) return false;
        }
    }
    
    int day, month, year, acc=0;
    day=stoi(date.substr (0,2));
    month=stoi(date.substr (3,2));
    year=stoi(date.substr (6,4));

    if(year<1990) return false;
    if(month>12||month<1) return false;
    if(day>getNumberOfDaysInMonth(month,year)||day<1) return false;



    return true;
}

string intToDate(int daysSince1990){
    int day =1, month =1, year =1990;
    while (daysSince1990>=365)
    {
        if(isLeapYear(year))daysSince1990-=366;
        else daysSince1990-=365; 
        year++;       
    }
    while (daysSince1990>=getNumberOfDaysInMonth(month,year))
    {
        daysSince1990-=getNumberOfDaysInMonth(month,year);
        month++;
    }

    
    day+=daysSince1990;
    string date="";

    if(day<10) date+="0"+to_string(day)+"/";
    else date += to_string(day)+"/";

    if(month<10) date+="0"+to_string(month)+"/";
    else date += to_string(month)+"/"; 

    date+= to_string(year);
    return date;   

    
    




}







//days Since 01/01/1990
int dateToInt(string date){
    int day, month, year, acc=0;
    day=stoi(date.substr (0,2));
    month=stoi(date.substr (3,2));
    year=stoi(date.substr (6,4));
    
    for(int iYear=1990; iYear<year;iYear++){

        if(isLeapYear(iYear)) acc+=366;
        else acc+=365;
    }

    for(int iMonth =1; iMonth<month;iMonth++){
        acc+=getNumberOfDaysInMonth(iMonth, year);        
    }
    acc+= day;
    //Correcion pq los dias del mes no empiezan por cero
    acc-=1;
    return acc;
}


//function will return total number of days
int  getNumberOfDaysInMonth(int month, int year)
{
	//leap year condition, if month is 2
	if( month == 2)
	{
		if(isLeapYear(year))	
			return 29;
		else	
			return 28;
	}
	//months that have 31 days
	else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8
	||month == 10 || month==12)	
		return 31;
	else 		
		return 30;
} 



bool isLeapYear(int year){

    if((year%400==0) || (year%4==0 && year%100!=0))	
        return true;
    else	
        return false;

}