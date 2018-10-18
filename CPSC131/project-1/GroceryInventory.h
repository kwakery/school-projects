#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "GroceryItem.h"
using namespace std;

class GroceryInventory {
private:
    vector<GroceryItem> _inventory;
    float _taxRate;

public:
    GroceryInventory();

    GroceryItem& getEntry(const string&);
    void addEntry(const string&, const int&, const float&, const bool&);
    float getTaxRate() const;
    void setTaxRate(const float&);

    void createListFromFile(const string&);
    float calculateUnitRevenue() const;
    float calculateTaxRevenue() const;
    float calculateTotalRevenue() const;

    GroceryItem& operator[](const int&);
};

/**
 * The default Constructor
 */
GroceryInventory::GroceryInventory() {
    _taxRate = 0.0;
}

/**
 * Gets the item to use
 * @param entry - the item's name to use
 * @return - the grocery item object
 */
GroceryItem& GroceryInventory::getEntry(const string& entry) {
    int size = _inventory.size(); // Size of _inventory vector
    for (int i = 0; i < size; i++) // Search for the item
    {
        if (_inventory[i].getName() == entry) // If the item is found, return its object
            return _inventory[i];
    }

    throw range_error("Could not find entry"); // If search cannot find item, return a null object
}

/**
 * Adds the item to the inventory
 * @param entry - the name of items
 * @param quantity - the quantity of the item
 * @param unitPrice - the price per unit of the item
 * @param isTaxable - true if the item is taxable, false if otherwise
 * @return - True if the key is valid and False otherwise
 */
void GroceryInventory::addEntry(const string& entry, const int& quantity, const float& unitPrice, const bool& isTaxable) {
    GroceryItem newItem(entry, quantity, unitPrice, isTaxable); // Initialize object for item

    _inventory.push_back(newItem); // Add object to vector
}

/**
 * Gets the tax rate of the store
 * @return - the tax rate
 */
float GroceryInventory::getTaxRate() const {
    return _taxRate;
}

/**
 * Sets the new tax rate to use for the store
 * @param newTaxRate - the tax rate to use
 */
 void GroceryInventory::setTaxRate(const float& newTaxRate) {
    _taxRate = newTaxRate * .01; // Turn percent to decimal to use in formula
 }

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
void GroceryInventory::createListFromFile(const string& filename) {
    ifstream input_file(filename);

    if (input_file.is_open()) {
        cout << "Successfully opened file " << filename << endl;
        string name;
        int quantity;
        float unit_price;
        bool taxable;
        while (input_file >> name >> quantity >> unit_price >> taxable) {
            addEntry(name, quantity, unit_price, taxable);
        }
        input_file.close();
    } else {
        throw invalid_argument("Could not open file " + filename);
    }
}

/**
 * Sets the key to use
 * @return - True if the key is valid and False otherwise
 */
float GroceryInventory::calculateUnitRevenue() const {
    float totalUnitRevenue = 0.0;
    int size = _inventory.size(); // Size of _inventory vector
    for (unsigned int i = 0; i < size; i++) // for each item in inventory, copy over to new
    {
        GroceryItem item = _inventory[i];

        totalUnitRevenue += item.getQuantity() * item.getUnitPrice(); // calculate revenue
    }

    return totalUnitRevenue;
}

/**
 * Sets the key to use
 * @return - True if the key is valid and False otherwise
 */
float GroceryInventory::calculateTaxRevenue() const {
    float totalTax = 0.0;
    int size = _inventory.size(); // Size of _inventory vector
    for (int i = 0; i < size; i++) // for each item in inventory, copy over to new
    {
        GroceryItem item = _inventory[i];
        if (item.isTaxable())
            totalTax += (item.getQuantity() * item.getUnitPrice()) * getTaxRate(); // item revenue * tax rate
    }

    return totalTax;
}

/**
 * Calculates the total total revenue
 * Formula: total unit revenue + total tax revenue
 * @return - calculated total revenue
 */
float GroceryInventory::calculateTotalRevenue() const {
    return calculateTaxRevenue() + calculateUnitRevenue();
}

/**
 * @return - return a reference to the nth item in the inventory
 */
GroceryItem& GroceryInventory::operator[](const int& index) {
    return _inventory[index];
}
