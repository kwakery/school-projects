#include <iostream>
#include <string>
#include "twitter.hpp"
using namespace std;

int main()
{
	/* Variables */
	bool isRunning = true;
	string name; // Username
	string tweet = ""; // Complete Tweet
	string tweets[100] = {}; // Tweet segments
	int numSegments = 0;

	/* Get username and store to variable */
	cout << "Please enter your username: ";
	cin >> name;
	cin.ignore();

	while (isRunning) // Run program until exit is entered
	{
		/* Prompt user to enter tweet until sentinel (Exit) is entered */
		cout << "Please enter your message (or input Exit to quit): ";
		getline(cin, tweet);

		if (tweet == "Exit" || tweet == "exit")
		{
			isRunning = false;
			break;
		}

		/* Split Tweet */
		splitTweets(tweet, tweets, &numSegments); // Split the tweet
		displaySplitTweet(tweets, numSegments, name); // Display the tweets
  }

	return 0;
}
