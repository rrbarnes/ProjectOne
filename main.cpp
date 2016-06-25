/*
 
 */

/* 
 * File:   main.cpp
 * Author: Rin
 *
 * Created on June 24, 2016, 6:52 PM
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;


class Product{
protected:
    // Data members
    string id;
    string category;
    string condition;

public:
    // Constructors
    Product();
    Product(string i, string cat, string cond);
    virtual ~Product();
    
    // Methods
};

// Default constructor method
Product::Product(){
    id = "";
    category = "";
    condition = "";
}

// Constructor method passed 3 strings
Product::Product(string i, string cat, string cond){
    id = i;
    category = cat;
    condition = cond;
}

// Destructor for default constructor
Product::~Product(){
}

int main(int argc, char** argv) {
    
    Product* myproduct = new Product("me", "big men", "brand new");
    cout << myproduct << endl;

    return 0;
}

