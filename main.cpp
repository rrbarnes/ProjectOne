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

// Constructor method passed 4 strings
//Item::Item(string t, string ava, string col, string pri)
//{
//    // Set fields based on passed parameters
//    title = t;
//    avail = ava;
//    color = col;
//    price = pri;
//}

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

/*
 * Function to open and read passed input file. If the file
 * does not exist, throw FileNotFoundException. Read each line of the file
 * then set the Item's appropriate field. Add these items into the passed
 * vector.
 */
string readFile(ifstream &inputFile, vector<Item*>* items)
{
    string line; // string to hold one line of the file
    int fieldCounter = 0; // initialize a field counter for each item
    Item* item = new Item(); // initialize very first item
    
    // Ensure the file was opened. If not, throw exception. 
    if ( !inputFile.is_open() )
    {
        cout << "Could not open file. Ensure your path is correct." << endl;
        throw ExceptionFileNotFound();
    }
    // Otherwise, read the file line by line.
    else
    {
        while (getline (inputFile, line)) // Loop through each line.
        {
            if (line != "**") // Fill the item's fields until you find **
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
                items->push_back(item); // add the item to the vector
                fieldCounter = 0; // "reset" the counter for next item
                item = new Item();// create a new item for the next
            }
        }
        inputFile.close(); // Close the input file
    }
}

/*
 * Get the file path from the user
 */
string getInput()
{
    string theInput; // to hold the file name or input from user
    cout << "Please input the full path of the input file or type 'exit' to exit:";
    getline (cin, theInput); // store the input
    return theInput;
}

int main(int argc, char** argv)
{   
    // Check command line arguments
    if (argc != 2) // only 2 arguments...the program name and file path
        cout << "usage: " << argv[0] << " <filepath>\n";
    else
    {
        vector<Item*>* googleItems = new vector<Item*>(); // Create a new vector of items
        ifstream filePath (argv[1]); // open the file and hold in filePath - the second argument should be file path
        
        try // try reading the file to set the items' fields
        {
            readFile(filePath, googleItems);
            cout << "File read and items filled." << endl;
        }
        catch (ExceptionFileNotFound fnf)
        {
            cout << "File not found. Please rerun with correct path.";
        }
    }
    
    return 0;
}

