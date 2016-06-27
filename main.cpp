/* 
 * File:   main.cpp - Contains 3 classes Product, Item, and 
 *                    FileNotFoundException. Contains main and helper 
 *                    functions to test all classes.
 * Author: Rin
 *
 * Created on June 24, 2016, 6:52 PM
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Exception.h"
using namespace std;

/*
 *  Class Product contains 3 members containing the id, category, and
 *  condition of the product
 */
class Product
{
protected:
    // Data members
    string id;
    string category;
    string condition;

public:
    // Constructors
    Product();
    //Product(string i, string cat, string cond);
    virtual ~Product();

    // Get and set methods for a Product
    int display();
    string getId();
    void   setId(string i);
    string getCategory();
    void   setCategory(string c);
    string getCondition();
    void   setCondition(string c);
};

// Default constructor method
Product::Product()
{
    // Initialize fields as empty strings
    id = "";
    category = "";
    condition = "";
}

// Constructor method passed 3 strings
//Product::Product(string i, string cat, string cond)
//{
//    // Set fields based on passed parameters
//    id = i;
//    category = cat;
//    condition = cond;
//}

// Destructor for default constructor
Product::~Product(){ }

// Get and set methods for the Product (put more commments/header comments)
string Product::getId(){return id;}
void   Product::setId(string i){id = i;}
string Product::getCategory(){return category;}
void   Product::setCategory(string c){category = c;}
string Product::getCondition(){return condition;}
void   Product::setCondition(string c){condition = c;}

/*
 * Display information about this product, with each field 
 * displayed on a new line.
*/
Product::display()
{
    cout << "Product id: " << id << "\n" <<
            "Product category: " << category << "\n" <<
            "Product condition: " << condition << "\n" << endl;
}

/*
 *  Class Item is a subclass of Product. It contains 4 members the title, price,
 *  availability, and color of the object.
*/
class Item : public Product
{
protected:
    // Data members
    string title;
    string avail;
    string color;
    string price;

public:
    // Constructors
    Item();
    //Item(string t, string ava, string col, string pri);
    virtual ~Item();

    // Get and set methods for an Item
    int display();
    string getTitle();
    void   setTitle(string t);
    string getAvail();
    void   setAvail(string ava);
    string getColor();
    void   setColor(string c);
    string getPrice();
    void   setPrice(string p);
};

// Default constructor method
Item::Item()
{
    // Initialize fields as empty strings
    title = "";
    avail = "";
    color = "";
    price = "";
}

// Destructor for default constructor
Item::~Item(){ }

// Return and set methods for the fields
string Item::getTitle(){return title;}
void   Item::setTitle(string t){title = t;}
string Item::getAvail(){return avail;}
void   Item::setAvail(string a){avail = a;}
string Item::getColor(){return color;}
void   Item::setColor(string c){color = c;}
string Item::getPrice(){return price;}
void   Item::setPrice(string p){price = p;}

/*
 * Overridden method from Public class displays all fields
 * of the Item class on a separate line. 
 */
Item::display()
{
    cout << "Item title: " << title << "\n" <<
            "Item availability: " << avail << "\n" <<
            "Item color: " << color << "\n" <<
            "Item price: " << price << endl;
}

/*
 * FileNotFoundException class extends Exception
 */
class ExceptionFileNotFound : public Exception{ };

/*
 * End Classes
 */

int main(int argc, char** argv)
{   
    // Create objects for use by main
    string line; // string to hold one line of the file
    string separator = "**"; // the string that separates products in the file
    int fieldCounter = 0; // initialize a field counter for each item in the file
    vector<Item*>* googleItems = new vector<Item*>; // Create a new vector of items
    Item* item = new Item(); // initialize very first item
    
    // Check command line arguments
    if (argc != 2) // only 2 arguments...the program name and file path
        cout << "usage: " << argv[0] << " <filepath>\n";
    else
    {
        ifstream inputFile (argv[1]); // open the file and hold in filePath - the second argument should be file path
        
        // Ensure the file was opened. If not, throw exception. 
        if ( !inputFile.is_open() )
        {
            cout << "Could not open file. Ensure your path is correct. Exiting..." << endl;
            throw ExceptionFileNotFound();
        }
        // Otherwise, read the file line by line.
        else
        {
            while (getline (inputFile, line)) // Loop through each line.
            {
                if ( line.find(separator) == string::npos ) // Fill the item's fields until you find **
                {
                    switch( fieldCounter ) // To determine which field we have
                    {
                        // Set each field based on current line for this Item
                        case 0:
                            item->setId(line);
                            break;
                        case 1:
                            item->setCategory(line);
                            break;
                        case 2:
                            item->setCondition(line);
                            break;
                        case 3:
                            item->setTitle(line);
                            break;
                        case 4:
                            item->setAvail(line);
                            break;
                        case 5:
                            item->setColor(line);
                            break;
                        case 6:
                            item->setPrice(line);
                            break;
                    }
                    fieldCounter++; // Increment the counter for the next Item field
                }
                else // If we've reached ** create a new Item for the next iteration
                {
                    googleItems->push_back(item); // add the item to the vector
                    fieldCounter = 0; // "reset" the counter for next item
                    Item* item = new Item();// create a new item for the next
                }
            }
        }
        inputFile.close(); // Close the input file
    }
    
    // Now that we have all the items stored in a vector, produce required output
    
    // Number of products is simply the size of the vector since it contains all the products
    cout << "Total number of products: " << googleItems->size();
    
    /*
     * The rest of the output required in the project specifications requires looping
     * through the products again to determine certain criteria. We will accomplish
     * this below, although a faster solution would be to do this while in the loop above.
    */
    
    // Loop through the products and store certain criteria
    // ints to count different criteria
    int newProducts = 0;
    int usedProducts = 0;
    int refurProducts = 0;
    // doubles for price specifications
    double maxPriceNew = 0.00;
    double maxPriceUsed = 0.00;
    double maxPriceRefur = 0.00;
    double minPriceNew = 999999.00;
    double minPriceUsed = 999999.00;
    double minPriceRefur = 999999.00;
    double totalPrice = 0.00;
    double avgPrice = 0.00;
    
    int size = googleItems->size(); // Store the size once so size() isn't called every iteration
    // Loop through the googleItems vector to determine certain criteria
    for (int i=0; i < size; i++)
    {
        Item* thisItem = googleItems->at(i); // Get the item from the vector
        double itemPrice = thisItem->getPrice();
        string itemCondition = thisItem->getCondition();
        totalPrice += itemPrice;
        if (itemCondition == "new")
        {
            newProducts++;
            if (itemPrice > maxPriceNew) maxPriceNew = itemPrice;
            if (itemPrice < minPriceNew) minPriceNew = itemPrice;
        }
        else if (itemCondition == "used")
        {
            usedProducts++;
            if (itemPrice > maxPriceUsed) maxPriceUsed = itemPrice;
            if (itemPrice < minPriceUsed) minPriceUsed = itemPrice;
        }
        else
        {
            refurProducts++;
            if (itemPrice > maxPriceRefur) maxPriceRefur = itemPrice;
            if (itemPrice < minPriceRefur) minPriceRefur = itemPrice;
        }
    }
    
    avgPrice = totalPrice/size;
    
    return 0;
}

