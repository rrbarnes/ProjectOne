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

/*
 *  Class Product contains 3 members containing the id, category, and
 *  condition of the product
 */
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
    int display();
    string getId();
    string getCategory();
    string getCondition();
};

// Return the id of the Product
Product::getId(){
    return id;
}

// Return the category of the product
Product::getCategory(){
    return category;
}

// Return the condition of the product
Product::getCondition(){
    return condition;
}

/*
 * Display information about this product, with each field 
 * displayed on a new line.
*/
Product::display(){
    cout << "Product id: " << id << "\n" <<
                "Product category: " << category << "\n" <<
                "Product condition: " << condition << "\n" << endl;
    
}

// Default constructor method
Product::Product(){
    // Initialize fields as empty strings
    id = "";
    category = "";
    condition = "";
}

// Constructor method passed 3 strings
Product::Product(string i, string cat, string cond){
    // Set fields based on passed parameters
    id = i;
    category = cat;
    condition = cond;
}

// Destructor for default constructor
Product::~Product(){ }

/*
 *  Class Item contains 4 members the title, price, availability, and
 *  color of the object.
*/
class Item : public Product{
protected:
    // Data members
    string title;
    string avail;
    string color;
    string price;

public:
    // Constructors
    Item();
    Item(string t, string ava, string col, string pri);
    virtual ~Item();
    
    // Methods
    int display();
};

/*
 * Function to open and read input file. If the file
 * does not exist, return false to the caller. Otherwise,
 * return true
 */
bool readFile(char fileName){
    string line; // string to hold one line of the file
    ifstream myFile ( fileName ); // open the file
    
    // 
    if ( !myFile.is_open() )
    cout<<"Could not open file\n";
    else {
   while ( getline (myFile,line) )
   {
   cout << line << '\n';
   }
myFile.close();
}
 }
}

int main(int argc, char** argv) {
    
    Product* myproduct = new Product("me", "big men", "brand new");
    myproduct->display();

    return 0;
}

