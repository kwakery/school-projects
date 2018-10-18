#pragma once

#include <string>
using namespace std;

class GroceryItem {
private:
    string _name;
    int _quantity;
    float _unitPrice;
    bool _taxable;

public:
    GroceryItem();
    GroceryItem(const string&, const int&, const float&, const bool&);

    string getName() const;
    void setName(const string&);
    int getQuantity() const;
    void setQuantity(const int&);
    float getUnitPrice() const;
    void setUnitPrice(const float&);
    bool isTaxable() const;
    void setTaxable(const bool&);
};

/**
 * Default Constrtor
 */
 GroceryItem::GroceryItem() {
    _name = "";
    _quantity = 0;
    _unitPrice = 0.0;
    _taxable = true;
 }

 /**
  * Constructor
  * @param name - the name to use
  * @param quantity - the quantity to use
  * @param unitPrice - the unitPrice to use
  * @param taxable - the taxable to use
  */
  GroceryItem::GroceryItem(const string& name, const int& quantity, const float& unitPrice, const bool& taxable) {
    _name = name;
    _quantity = quantity;
    _unitPrice = unitPrice;
    _taxable = taxable;
  }

/**
 * Gets the grocery item's name
 * @return - name of the grocery item
 */
string GroceryItem::getName() const {
    return _name;
}

/**
 * Sets the name to use
 * @param newName - new grocery item name
 */
void GroceryItem::setName(const string& newName) {
    _name = newName;
}

/**
 * Gets the total quantity of grocery items
 * @return - object's quantity
 */
int GroceryItem::getQuantity() const {
    return _quantity;
}

/**
 * Sets the quantity to use
 * @param newQuantity - new quantity to replace old
 */
void GroceryItem::setQuantity(const int& newQuantity) {
    _quantity = newQuantity;
}

/**
 * gets the price per unit of the grocery item
 * @return - price per unit
 */
float GroceryItem::getUnitPrice() const {
    return _unitPrice;
}

/**
 * Sets the unit price to use
 * @param newUnitPrice - price to use
 */
void GroceryItem::setUnitPrice(const float& newUnitPrice) {
    _unitPrice = newUnitPrice;
}

/**
 * Check if the grocery item is taxable
 * @return - True if the item is taxable and false otherwise
 */
bool GroceryItem::isTaxable() const {
    return _taxable;
}

/**
 * Sets the taxable to use
 * @param newTaxable - new taxable to use
 */
void GroceryItem::setTaxable(const bool& newTaxable)
{
    _taxable = newTaxable;
}
