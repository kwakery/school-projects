#include <iostream>
#include <string>
#include "twitter.hpp"

using namespace std;

int main()
{
	/* Variables */
	string username;
	string message;

	/* Prompt user for information about tweet */
	cout << "Please enter your username: ";
	cin >> username;
	cin.ignore();

	cout << "Please enter your message: ";
	getline(cin, message);

	/* Create TweetStream object */
	TweetStream stream(username);
	stream.addMessage(message);
	
	/* Display all tweets */
	stream.display();

	return 0;
}
