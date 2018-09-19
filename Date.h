// Final Project Milestone 1
//
// Version 1.0
// Date: July 9 2018
// Author: Miguel Roncanico
//student number: 151091170
// Description:
//DECLARES DATE CLASS, MEMBER FUNCTIONS AND DATA MEMBERS
//INCLUDES:
//  INPUT VALIDATION
//  ERROR HANDLING
//  OVERLOADED I/O OPERATORS
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include <iostream>
#ifndef AMA_DATE_H
#define AMA_DATE_H
#define max_year 2030
#define min_year 2000
#define NO_ERROR 0 //DATE IS VALID
#define CIN_FAILED 1 //ISTREAM FAILED ON INFORMATION ENTRY
#define YEAR_ERROR 2 // YEAR VALUE IS INVALID
#define MON_ERROR 3 // MONTH VALUE IS INVALID
#define DAY_ERROR 4 // DAY VALUE IS INVALDID

namespace AMA {

  class Date {
        int year, month, day;
        int comparator;
        int errorState;

        int mdays(int, int)const;
        void errCode(int);
 
  public:

    //******CONSTRUCTORS*********
    Date(); //default
    Date(int, int, int); //three argument

    //******OPERATORS************
    bool operator==(const Date&) const;
    bool operator!=(const Date&) const;
    bool operator<(const Date&) const;
    bool operator>(const Date&) const;
    bool operator<=(const Date&) const;
    bool operator>=(const Date&) const;
    
    //*******QUERIES AND MODIFIERS**********
    int errCode() const;
    bool bad() const;
    bool isEmpty() const;
    int validString(char* string) const;
    int validDate(int, int, int) const;


    std::istream& read(std::istream&);
    std::ostream& write(std::ostream&) const;

  };

std::ostream& operator<<(std::ostream&, const Date&);
std::istream& operator>>(std::istream&, Date&);

}

#endif