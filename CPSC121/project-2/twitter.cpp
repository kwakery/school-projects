#include <iostream>
#include <string>
#include "twitter.hpp"

using namespace std;

/* Displays formatted tweet */
void Tweet::display()
{
	cout << "@" << username << ": " << message << endl;
}

/* Add Tweet object to array */
void TwitterManager::addTweet(Tweet tweet)
{
	tweets[0] = tweet;
}

/* Add Tweet object to array @ specified index */
void TwitterManager::addTweet(Tweet tweet, int index)
{
	tweets[index] = tweet;
}

/* Calculates the number of segments based on the character limit */
int TwitterManager::calcSegments()
{
	/* Variables */
	double segments;
	int newSegments;
	int charLimit = 280; // Twitter character limit currently @ 280

	/* Calculate number of splits and round up if necessary */
	segments = message.length() / static_cast<double>(charLimit);
	newSegments = segments;
	if (segments > newSegments)
		newSegments++;

	/* Return calculated number of splits */
	return newSegments;
}

/* Recursively gets position of last character that is a space or punctuation */
int TwitterManager::rGetLastPuncPos(int currPos)
{
	char currChar = message[currPos];
	
	if (currPos == 0) // If there are no spaces or punctuation, return position 0
		return 0;

	if (currChar != ' ' && currChar != ',' && currChar != '.' && currChar != '!' && currChar != '?') // check if character at current position is not a limit char
		return rGetLastPuncPos(currPos - 1); // Keep going down until we find a limit char
	else
		return currPos; // Any character other than a space
}

/* Splits the provided message up based on the given number of segments */
void TwitterManager::splitTweets()
{
	length = calcSegments(); // Calculate number of splits needed
	
	Tweet tweet; // Create temporary tweet object
	tweet.setUsername(username); // Set username of tweet object to the same username of the manage
	
	if (length > 1) // If the number of segments is greater than 1
	{
		for (int i = 0; i < length; i++)
		{
			int currPos = 0;
			int endPos = 273; // Split on the 274th char to include pages
			
			endPos = rGetLastPuncPos(endPos); // Get position of last split char
			
			if (message.length() < endPos) // If there are less than the endPos # of characters then we substring up to the end of the string
				endPos = message.length() - 1;
			else if (endPos == 0) // if the endPos == 0 then we know there are no spaces/punctuation found
			{
				if (message.length() < 273)
					endPos = message.length() - 1;
				else endPos = 273;
			}
			/* Format message */

			string tempMsg;
			if (i == length - 1) // If on last segment, just substring to end of message
				tempMsg = message.substr(0, message.length());
			else
				tempMsg = message.substr(0, endPos + 1);

			tempMsg.append(" (").append(to_string(i + 1)).append("/").append(to_string(length)).append(")");
			
			tweet.setMessage(tempMsg); // Save message to tweet object
			addTweet(tweet, i); // Add tweet to array

			/* Update message */
			message = message.substr(endPos + 1);
		}
	} 
	else 
	{
		tweet.setMessage(message);
		addTweet(tweet);
	}
}

/* Invoke display function of all Tweet objects in array */
void TwitterManager::display()
{
	if (length == 1)
		tweets[0].display();
	else
		for (int i = 0; i < length; i++)
			tweets[i].display();
}

