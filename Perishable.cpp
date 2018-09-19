#include "Perishable.h"
using namespace AMA;

namespace AMA {
    Perishable::Perishable() : Product('P'){
    }

    //stores perishable information in file
    std::fstream& Perishable::store(std::fstream& file, bool newLine) const{
        Product::store(file, false);    // store product information
        file << ',' << date;   // store date info

        if(newLine){
            file << std::endl;
        }
    return file;
    }

    std::fstream& Perishable::load(std::fstream& file){
        Product::load(file); // load product info
        date.Date::read(file); //read date info from the file
        return file;
    }

    //calls the Product class write with 'os' and 'linear', 
    //checks for linear or multiline formatting, prints expiry date
    std::ostream& Perishable::write(std::ostream& os, bool linear) const{
        Product::write(os, linear); // Product member function
        if(state.ErrorState::isClear()){ //checks for errors before printing
            if(linear){         // linear output
                os << date;
            }else{              //multiline formatting 
                os <<std::endl << " Expiry date: " << date;
            }
        }
        return os;
    }

    std::istream& Perishable::read(std::istream& is){
        Product::read(is); // read product information

        if(!is.fail()){ //if data has been extracted successfully
            int year, month, day;
            std::cout << " Expiry date (YYYY/MM/DD): ";
            is >> year;
            is.ignore();
            is >> month;
            is.ignore();
            is >> day;
            Date temp = Date(year, month, day); //instantiates temporary date object, constructor validates information
            if(temp.bad()){ //checks for any errors
                switch(temp.errCode()){ // determines error code and store appropriate message
                    case CIN_FAILED:
                        state.message("Invalid Date Entry");
                        break;
                    case YEAR_ERROR:
                        state.message("Invalid Year in Date Entry");
                        break;
                    case MON_ERROR:
                        state.message("Invalid Month in Date Entry");
                        break;
                    case DAY_ERROR:
                        state.message("Invalid Day in Date Entry");
                        break;
                }
                is.setstate(std::ios::failbit); // set failbit

            }else
                date = temp; // if object does not contain errors, store temp into date
        }
        return is;    
    }
    
    const Date& Perishable::expiry() const{
        return date; // expiry date of perishable object
    }

}
