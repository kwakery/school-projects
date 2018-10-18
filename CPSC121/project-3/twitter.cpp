#include "twitter.hpp"

/* Constants */
const int splitPos = 273; // Position to split messages on
const int charLimit = 280; // Character limit of a tweet

/* --[ Tweet Functions ]-- */

/* Displays the tweet */
void Tweet::display()
{
    cout << "@" << username << ": " << message << endl;
}
    
/* --[ MultiTweet Functions ]-- */

/* Calculates the number of segments of the message based on the character limit */
int MultiTweet::calcSegments()
{
	/* Variables */
	double segments;
	int newSegments;

	/* Calculate number of splits and round up if necessary */
	segments = getMessage().length() / static_cast<double>(charLimit);
	newSegments = segments;

	if (segments > newSegments)
		newSegments++;

	/* Return calculated number of splits */
	return newSegments;
}

/* Recursively gets the position of the last punctuation */
int MultiTweet::rGetLastPuncPos(int currPos)
{
	char currChar = getMessage()[currPos];
	
	if (currPos == 0) // If there are no spaces or punctuation, return position 0
		return 0;

	if (currChar != ' ' && currChar != ',' && currChar != '.' && currChar != '!' && currChar != '?' && currChar != ';' && currChar != '-') // check if character at current position is not a limit char
		return rGetLastPuncPos(currPos - 1); // Keep going down until we find a limit char
	else
		return currPos; // Any character other than a space
}

/* Splits the provided message based on size of MultiTweets */
void MultiTweet::splitTweets()
{
	string message = getMessage();
	size = calcSegments(); // Calculate number of splits needed

	for (int i = 0; i < size; i++)
	{
		int currPos = 0;
		int endPos = splitPos; // Ending position of each message
			
		endPos = rGetLastPuncPos(endPos); // Get position of last split char
			
		if (message.length() < endPos) // If there are less than the endPos # of characters then we substring up to the end of the string
			endPos = message.length() - 1;
		else if (endPos == 0) // if the endPos == 0 then we know there are no spaces/punctuation found
		{
			if (message.length() < splitPos)
				endPos = message.length() - 1;
			else endPos = splitPos;
		}
        
		/* Format message */
		string tempMsg;
		if (i == size - 1) // If on last segment, just substring to end of message
			tempMsg = message.substr(0, message.length());
		else
			tempMsg = message.substr(0, endPos + 1);

		tempMsg.append(" (").append(to_string(i + 1)).append("/").append(to_string(size)).append(")");
			
		subMessages[i] = tempMsg; // Save message to subMessages

		/* Update message */
		message = message.substr(endPos + 1);
	}
}


/* Displays all the messages in the array */
void MultiTweet::display()
{
	for (int i = 0; i < size; i++)
		cout << "@" << getUsername() << ": " << subMessages[i] << endl;
}

/* --[ TweetStream Functions ]-- */

/* Sorts messages into the corresponding objects and adds to array */
bool TweetStream::addMessage(string message)
{
	if (message.length() > 280) // Check # of characters
		tweets[size] = new MultiTweet(username, message); // add new MultiTweet object to array
	else
		tweets[size] = new Tweet(username, message); // add new Tweet object to array

	size++; // Update size
}

/* Displays each message in array */
void TweetStream::display()
{
	for (int i = 0; i < size; i++)
	{
		tweets[i]->display();
	}
}
