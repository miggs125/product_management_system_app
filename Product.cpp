#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Product.h"
namespace AMA {

    void Product::name(const char* prodName){
        if(prodName == nullptr || prodName[0] == '\0' || !std::strcmp(prodName,""))
            productName = nullptr;
        else{
            int length = std::strlen(prodName);
            productName = new char[length+1];
            std::strcpy(productName, prodName);
        }
    }

    const char* Product::name() const{ //Returns product name
        return productName;
    }

    const char* Product::sku() const{ //returns product sku
        return productSku;
    }

    const char* Product::unit() const{ //returns unit description
        return prodUnit;
    }

    bool Product::taxed() const{  //returns boolean for taxable products
        return taxable;
    }

    double Product::price() const{  //returns the price
        return unitPrice;
    }

    double Product::cost() const{   //returns the price*(1+tax)
        double cost = unitPrice;
        if(taxed())
            cost *= (1+CURR_TAX);
        return cost;
    }

    void Product::message(const char* ErrMsg){ //returns any error message if found
        state.message(ErrMsg);
    }

    bool Product::isClear() const{ // returns boolean for any error state within the object
        return state.isClear();
    }

    Product::Product(char prodType){ // zero-no argument constructor
        type = prodType;         
        productSku[0] = 0;
        prodUnit[0] = 0;
        productName = nullptr;
        onHand = 0;
        required = 0;
        unitPrice = 0;
        taxable = true;
    }

    Product::Product(const char* sku, const char* name, const char* unit, //seven argument constructor. last 3 values have default
    int qty, bool taxMe, double price, int needed): Product(){
        strcpy(productSku,sku);
        strcpy(prodUnit,unit);
        this->name(name);
        onHand = qty;
        taxable = taxMe;
        unitPrice = price;
        required = needed;        
    }

    Product::Product(const Product& original){ // copy constructor
        productName = nullptr;
        *this = original;       
    }

    Product& Product::operator=(const Product& other){
        onHand = other.onHand;
        required = other.required;
        unitPrice = other.unitPrice;
        type = other.type;
        taxable = other.taxable;
        strcpy(productSku,other.productSku);
        strcpy(prodUnit,other.prodUnit);
        
        //if(other.productName != nullptr)
        name(other.productName);
        //else this->name = nullptr;
        return *this;
    }

    Product::~Product(){
        delete [] productName;
    }

    std::fstream& Product::store(std::fstream& file, bool newLine) const{
        file << type << ','
        << productSku << ',' << productName
        << ',' << prodUnit << ',' << taxable
        << ',' << unitPrice << ',' << onHand
        << ',' << required;
        if(newLine)
            file << std::endl;
        return file;
    }

    std::fstream& Product::load(std::fstream& file){
        char ftype;
        bool taxBool;
        double fprice;
        int fqty;
        int freq;        

        if(file.is_open()){
            char* fname = new char[max_name_length +1];
            char* funit = new char[max_unit_length +1];
            char* fsku = new char[max_sku_length +1];

            file.getline(fsku,max_sku_length, ',');
            file.getline(fname,max_name_length,',');
            file.getline(funit,max_unit_length,',');
            file >> taxBool;
            file.ignore();
            file >> fprice;
            file.ignore();
            file >> fqty;
            file.ignore();
            file >> freq;
            file.ignore();

            

            Product temp(fsku, fname, funit,fqty, taxBool,fprice,freq);
            ftype = type;
            *this = temp;
            type = ftype;

            delete [] fname;
            delete [] funit;
            delete [] fsku;
        }    
        return file;
    }

    std::ostream& Product::write(std::ostream& out, bool linear) const{ //writes a non-empty object to the ostream
        
        if(state.isClear()){ //check for invalid input
            //check for linear output
            if(linear){ // linear output
            out << std::setfill(' ') << std::setw(max_sku_length) << std::left << productSku << "|";
            
            // check for nullptr in name and print "" instead
            if(!name()){ 
                out << std::setfill(' ') << std::setw(20) << std::left << "" << "|";
            }else
                out << std::setfill(' ') << std::setw(20) << std::left << name() << "|"; 
            //continue output
            out << std::setfill(' ') << std::setw(7) << std::right <<std::fixed << std::setprecision(2) << cost() << "|";
            out << std::setfill(' ') << std::setw(4) << std::right << quantity() << "|";
            out << std::setfill(' ') << std::setw(max_unit_length) << std::left << prodUnit << "|";
            out << std::setfill(' ') << std::setw(4) << std::right << qtyNeeded() << "|";
            }else{ // formatted output, multiline 
                out << " Sku: " << sku()<< std::endl
                << " Name (no spaces): " << name() << std::endl
                << " Price: " <<  price() << std::endl
                << " Price after tax: ";
                if(taxed()) //check if product is taxed
                    out << cost() << std::endl;
                else
                    out << "N/A" << std::endl;
                out << " Quantity on Hand: " << quantity() << " " << unit() << std::endl
                << " Quantity needed: " << qtyNeeded();                        
            }
        } else
            out << state.message();
        
        return out;
    }

    std::istream& Product::read(std::istream& is){
        //the following variables will hold user input during validation
        char Sku[max_sku_length +1];
        char Name[max_name_length + 1];
        char Unit[max_unit_length + 1];
        char answer;
        double thePrice;
        int stock;
        int need;
        char ftype;

        while(true){
            is.clear(); //clear the istream status
            //is.ignore(2000,'\n'); //clear the input buffer
            std::cout << " Sku: ";
            is.getline(Sku,max_sku_length);  //store sku in temp variable
            std::cout << " Name (no spaces): ";  
            is.getline(Name,max_name_length);  //store sku in
            std::cout << " Unit: ";
            is.getline(Unit, max_unit_length); // store name in temp variable
            std::cout << " Taxed? (y/n): ";
            is.get(answer);                   
            if(is.fail() ||(answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N')){ // validate answer (char)
                is.setstate(std::ios::failbit);
                state.message("Only (Y)es or (N)o are acceptable");
            }else{
                std::cout << " Price: ";
                is >> thePrice;
                if(is.fail()){                          //validate thePrice (double)
                    is.setstate(std::ios::failbit);
                    state.message("Invalid Price Entry");
                }else{
                    std::cout << " Quantity on hand: ";
                    is >> stock;
                    if(is.fail()){                      //validate stock (int)
                        is.setstate(std::ios::failbit);
                        state.message("Invalid Quantity Entry");
                    }else{
                        std::cout << " Quantity needed: ";
                        is >> need;
                        if(is.fail()){              //validate need (int)
                            is.setstate(std::ios::failbit);
                            state.message("Invalid Quantity Needed Entry");
                        }else{
                            bool Taxable;
                            answer == 'y' || answer == 'Y' ? Taxable = true : Taxable = false; 
                            ftype = type;
                            Product temp(Sku,Name,Unit,stock,Taxable,thePrice,need);
                            *this = temp;
                            type = ftype;
                            state.clear();
                        }
                    }
                }
            }
            break; // kill loop
        }
        is.ignore(2000,'\n');
        return is;
    }

    bool Product::operator==(const char* rhs) const{
        return !std::strcmp(rhs,productSku);
    }

    double Product::total_cost() const {
        double total;
        total = this->cost() * onHand;
        return total;
    }

    void Product::quantity(int unitNums){
        onHand  = unitNums;
    }

    bool Product::isEmpty() const {
        return !productName;
    }

    int Product::qtyNeeded() const{
        return required;
    }

    int Product::quantity() const{
        return onHand;
    }

    bool Product::operator>(const char* sku) const{
        return productSku > sku;
    }

    bool Product::operator>(const iProduct& lhs) const{
        return *this > dynamic_cast<const Product&>(lhs).productSku; 
    }

    int Product::operator+=(int n){
        if(n > 0)
            onHand += n;
        return onHand;
    }

    std::ostream& operator<<(std::ostream& os, const iProduct& output){
        return output.write(os, true);
    }

    std::istream& operator>>(std::istream& is, iProduct& product){
        return product.read(is);
    }

    double operator+=(double& cost, const iProduct& product){
        return cost + product.total_cost(); 
    }
}