#ifndef GroceryCheckout_h
#define GroceryCheckout_h

#include <fstream>
#include <map>
#include <vector>

using namespace std;

struct GroceryItem
{
	GroceryItem() { }
	GroceryItem(const string& name, int quantity, float price, bool taxable) : name_(name), quantity_(quantity), price_(price), taxable_(taxable) { }

	string	name_;
	int		quantity_;
	float	price_;
	bool	taxable_;
};

struct ReceiptItem
{
	ReceiptItem() { }
	ReceiptItem(const string& name, float price) : name_(name), price_(price) { }

	string	name_;
	float	price_;
};

struct	Receipt
{
	vector<ReceiptItem>	item_;
	float				subtotal_;
	float				taxAmount_;
	float				total_;
};

class GroceryInventory
{
	public:
		bool			AddItem(const string&, int, float, bool);
		void			CreateFromFile(const string&);
		Receipt			CreateReceipt(const string&);
		GroceryItem*	FindItem(const string&);
		bool			RemoveItem(const string&);
		void			SetTaxRate(float);
		size_t			Size();

	private:
		map<string, GroceryItem> inventory_; // Map holding the name of the item as a key and its corresponding GroceryItem for its value
		float taxrate_; // Global tax rate of the store
};

#endif
