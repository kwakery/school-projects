#include <iostream>
#include <string>
using namespace std;

/* Calculates the number of segments based on the character limit */
int calcSegments(string tweet)
{
	/* Variables */
	double segments;
	int newSegments;
	int charLimit = 280; // Twitter character limit currently @ 280

	/* Calculate number of splits and round up if necessary */
	segments = tweet.length() / static_cast<double>(charLimit);
	newSegments = segments;
	if (segments > newSegments)
		newSegments++;

	/* Return calculated number of splits */
	return newSegments;
}

/* Display the tweets in a formatted way */
void displaySplitTweet(string tweets[], int numSegments, string name)
{
	if (numSegments == 1) // If there are no splits, just return name & message
		cout << "@" << name << ": " << tweets[0] << endl;
	else // Else return formatted messages
		for (int i = 0; i < numSegments; i++)
			cout << "@" << name << ": " << tweets[i] << " (" << (i + 1) << "/" << numSegments << ")" << endl;
}

/* Recursively gets position of last character that is a space */
int getLastPuncPos(string tweet, int currPos)
{
	char currChar = tweet[currPos];

	if (currChar != ' ' && currChar != ',' && currChar != '.' && currChar != '!' && currChar != '?') // check if character at current position is not a limit char
		return getLastPuncPos(tweet, (currPos - 1)); // Keep going down until we find a limit char
	else
		return currPos; // Any character other than a space
}

/* Splits the provided message up based on the given number of segments */
void splitTweets(string tweet, string tweets[], int *numSegments)
{
    *numSegments = calcSegments(tweet); // Calculate number of splits needed

	if (*numSegments > 1)
	{
		for (int i = 0; i < *numSegments; i++)
		{
			int currPos = 0;
			int endPos = 279;

			if (tweet.length() < endPos) // If last segment, use length for endPos
				endPos = tweet.length() - 1;
			else // Get position of last split char
				endPos = getLastPuncPos(tweet, endPos);

			tweets[i] = tweet.substr(currPos, endPos + 1);

			/* Update tweet */
			tweet = tweet.substr(endPos + 1);
		}
	} else tweets[0] = tweet;
}
