#include	<iostream>
#include <stdexcept>
#include	"GroceryCheckout.h"

using namespace std;

/* Adds the given item to the map
 * Needs to check for duplicates
 * @param name - name of the item
 * @param quantity - # of the item the shop has
 * @param price - cost of the item
 * @param taxable - true if the item can be taxed, false if it can't
 * @return - true if the operation was successful, false if it failed
 */
bool GroceryInventory::AddItem(const string& name, int quantity, float price, bool taxable)
{
		if (inventory_.count(name) != 0) // Check if item already exists
				return false; // Operation

		GroceryItem item(name, quantity, price, taxable); // Create GroceryItem from given data
		inventory_.emplace(name, item); // Add item to the map

		return true;
}

/* Reads an inventory file and adds each item to the map
 * @param fileName - name of the file to read
 */
void GroceryInventory::CreateFromFile(const string& fileName)
{
	  ifstream	file(fileName);
		string		name;
		float		price;
		int			quantity;
		bool		taxable;

		if (file.is_open())
		{
				while (true)
				{
						file >> name >> quantity >> price >> taxable;

						if (!file.fail())
								AddItem(name, quantity, price, taxable);
						else break;

			   }

			   file.close();
		}
		else cout << "Could not open file " + fileName << endl;
}

/* Generates a receipt from a file containing the user's purchases
 * @param fileName - name of the file to read from
 * @return - receipt data
 */
Receipt GroceryInventory::CreateReceipt(const string& fileName)
{
		ifstream file(fileName);
		vector<ReceiptItem> groceries; // Vector that contains the receipt items
		Receipt receipt;
		receipt.subtotal_ = 0.0;
		receipt.taxAmount_ = 0.0;

		string name;
		while (file >> name) // Read each piece of data separated by a space/new line
		{
				GroceryItem* item = FindItem(name); // Get the item
				item->quantity_--; // Change the quantity since it has been purchased
				receipt.subtotal_ += item->price_;

				if (item->taxable_) // Check if the item is taxable
						receipt.taxAmount_ += item->price_ * taxrate_; // Update tax total

				ReceiptItem ritem(name, item->price_); // Create a ReceiptItem with its name as the key and its price as the value
				groceries.push_back(ritem); // Push item to the receipt vector
		}

		/* Add remaining data to receipt */
		receipt.item_ = groceries;
		receipt.total_ = receipt.subtotal_ + receipt.taxAmount_;

		return receipt; // Return receipt
}

/* Finds the specified item in the map
 * @param name - name of the item to find
 * @return - the item object
 */
GroceryItem* GroceryInventory::FindItem(const string& name)
{
		if (inventory_.count(name) == 0) // Check if inventory has the item
				return nullptr;

		return &(inventory_.at(name)); // Return the pointer to the item
}

/* Removes the specified item from the map
 * @param name - name of the item
 * @return - true if the operation was successful, false if it failed
 */
bool GroceryInventory::RemoveItem(const string& name)
{
		return inventory_.erase(name); // erase() for maps returns true/false already
}

/* Sets the tax rate of the store
 * @param taxRate - tax rate in decimals
 */
void GroceryInventory::SetTaxRate(float taxRate)
{
		taxrate_ = taxRate * .01; // % -> decimal
}

/* Gets the current size of the map
 * @return - size
 */
size_t GroceryInventory::Size()
{
		return inventory_.size();
}
