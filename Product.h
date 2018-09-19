#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H
#define MAX_CHAR_SKU 7
#define MAX_CHAR_DESC 10
#define MAX_CHAR_NAME 75
#define CURR_TAX 0.13

#include <iostream>
#include <fstream>
#include "ErrorState.h"
#include "iProduct.h"

namespace AMA {
        const int max_sku_length = MAX_CHAR_SKU;
        const int max_name_length = MAX_CHAR_NAME;
        const int max_unit_length = MAX_CHAR_DESC;
    
    class Product : public iProduct {        
        
        protected:
        
        char type;
        char productSku[MAX_CHAR_SKU +1];
        char prodUnit[MAX_CHAR_DESC +1];
        char* productName;
        int onHand;
        int required;
        double unitPrice;
        bool taxable;
        ErrorState state;

        void name(const char*);
        const char* name() const;
        const char* sku() const;
        const char* unit() const;
        bool taxed() const;
        double price() const;
        double cost() const;
        void message(const char*);
        bool isClear() const;

        public:

        //CONSTRUCTORS
        Product(char prodType = 'N'); //zero to one argument constructor
        Product(const char*, const char*, const char*, 
        int qty = 0, bool taxMe = true, double price = 0, int needed = 0);
        ~Product();
        
        Product(const Product&); //copy constructor
        Product& operator=(const Product&); // assignment operator
        
        std::fstream& store(std::fstream&, bool newLine = true) const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& os, bool linear) const;
        std:: istream& read(std::istream& is);
        bool operator==(const char*) const;
        double total_cost() const;
        void quantity(int);
        bool isEmpty() const;
        int qtyNeeded() const;
        int quantity() const;
        bool operator>(const char*) const;
        bool operator>(const iProduct&) const;
        int operator+=(int);
    };

    std::ostream& operator<<(std::ostream&, const iProduct&);
    std::istream& operator>>(std::istream&, iProduct&);
    double operator+=(double&, const iProduct&);
}


#endif