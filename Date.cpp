// Final Project Milestone 1
//
// Version 1.0
// Date: July 9 2018
// Author: Miguel Roncanico
//student number: 151091170
// Description:
//DEFINES DATE CLASS, MEMBER FUNCTIONS AND DATA MEMBERS
//INCLUDES:
//  INPUT VALIDATION
//  ERROR HANDLING
//  OVERLOADED I/O OPERATORS
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include <string.h>
#include "Date.h"

namespace AMA {

  // number of days in month mon_ and year year_
  //
    int Date::mdays(int mon, int year)const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int month = mon >= 1 && mon <= 12 ? mon : 13;
        month--;
        return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    void Date::errCode(int n){ //sets errorState
        switch(n){
            case 0:
                errorState = NO_ERROR;
                break;
            case 1:
                errorState = CIN_FAILED; // input error
                break;
            case 2:
                errorState = YEAR_ERROR;
                break;
            case 3:
                errorState = MON_ERROR;
                break;
            case 4:
                errorState = DAY_ERROR;
                break;
        }
    }

    //******CONSTRUCTORS*********
    Date::Date(){    //default
        errorState = NO_ERROR;
        comparator = 0;
        year = month = day = 0;
    } 

    Date::Date(int y, int m, int d){ //three argument
        if(!validDate(y,m,d)){
            year = y;
            month = m;
            day = d;
            errCode(NO_ERROR);
            comparator = year*372 + month*13+day;
        }else {
            errCode(validDate(y,m,d)); // determine error type and set errorState
            //*this = Date();             //store in emtpy state
        }
    }

    //******OPERATORS************
    bool Date::operator==(const Date& rhs) const{
        bool equal = false;
        if(!isEmpty() && !rhs.isEmpty()){
            equal = rhs.year == year;
            if(equal)
                equal = rhs.month == month;
            if(equal)
                equal = rhs.day == day;   
        }
        return equal;
    }

    bool Date::operator!=(const Date& rhs) const{
        bool notEqual = false;
        if(!isEmpty() && !rhs.isEmpty())
            notEqual = !(*this == rhs); 
        return notEqual; 
    }
    
    bool Date::operator<(const Date& rhs) const{
        bool less = false;
        if(!isEmpty() && !rhs.isEmpty()){
            less = comparator < rhs.comparator;
        }
        return less;
    }
    
    bool Date::operator>(const Date& rhs) const{
        bool greater = false;
        if(!isEmpty() && !rhs.isEmpty()){
            greater = comparator > rhs.comparator;
        }
        return greater;
    }
    
    bool Date::operator<=(const Date& rhs) const{
        bool lessOrEqual;
        if(!isEmpty() && !rhs.isEmpty()){
            lessOrEqual = *this < rhs || *this == rhs;
        }
        return lessOrEqual;
    };
    
    bool Date::operator>=(const Date& rhs) const{
        bool greaterOrEqual;
        if(!isEmpty() && !rhs.isEmpty()){
            greaterOrEqual = *this > rhs || *this == rhs;
        }
        return greaterOrEqual;
    };
    
    //*******QUERIES AND MODIFIERS**********
    int Date::errCode() const{
        return errorState;
    };

    bool Date::bad() const{
        return errorState;
    };

    bool Date::isEmpty() const{
        bool empty = true;
        if(year && month && day)
            empty = false;
        return empty;
    };

    std::istream& Date::read(std::istream& istr){
        int year, month, day; //temp variables for validation
        istr >> year;
        istr.get();
        istr >> month;
        istr.get();
        istr >> day;

        if(validDate(year,month,day) == 0){ // NO_ERROR == 0
            this->year = year;
            this->month = month;
            this->day = day;
        } else
            errCode(validDate(year,month, day));    //set error type
        return istr;
    };

    int Date::validDate(int year, int month, int day) const{ //validates input
        int error = NO_ERROR;
        if(year == 0 || month == 0 || day == 0)
            error = CIN_FAILED;
        else if(2000 > year || 2030 < year)
            error = YEAR_ERROR;
        else if(12 < month || month < 1)
            error = MON_ERROR;
        else if(mdays(month,year) < day || day < 1)
            error = DAY_ERROR;
        return error;
    }

    std::ostream& Date::write(std::ostream& ostr) const{
        if(year)
            ostr << std::setfill('0') << std::setw(4) << year <<"/";
        else
            ostr << year <<"/";
        ostr << std::setfill('0') << std::setw(2) << month << "/" 
        << std::setfill('0') << std::setw(2) <<day;

        return ostr;
    };

    std::ostream& operator<<(std::ostream& stream, const Date& date){
        date.write(stream);
        return stream;
    };

    std::istream& operator>>(std::istream& ist, Date& date){
        date.read(ist);
        return ist; 
    };
}
   