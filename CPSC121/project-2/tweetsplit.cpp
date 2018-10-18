#include <iostream>
#include <string>
#include "twitter.hpp"

using namespace std;

int main()
{
	/* Variables */
	string username;
	string message;
	
	/* Prompt user for username and message */
	cout << "Please enter your username: ";
	cin >> username;
	cin.ignore();

	cout << "Please input your message: ";
	getline(cin, message);

	/* Initialize TwitterManager Object */
	TwitterManager mgr(username, message);
	
	/* Display all tweets */
	mgr.display();
	
	return 0;
}
