#ifndef TWITTER_HPP // This code prevents multiple includes of twitter.hpp
#define TWITTER_HPP

#include <iostream>
#include <string>
using namespace std;

class Tweet
{
	private:
		string username;
		string message;
		int charLength;
	public:
		/* Constructors */
		Tweet()
		{
			username = "";
			message = "";
			charLength = 0;
		}
		
		Tweet(string newUsername, string newMessage)
		{
			username = newUsername;
			message = newMessage;
			charLength = message.length();
		}

		/* Getters */
		string getUsername()
		{
			return username;
		}

		string getMessage()
		{
			return message;
		}

		int getCharLength()
		{
			return charLength;
		}
		
		/* Setters */
		void setUsername(string newUsername)
		{
			username = newUsername;
		}

		void setMessage(string newMessage)
		{
			message = newMessage;
			charLength = newMessage.length();
		}

		/* Prototypes */
		void display();
};

class TwitterManager
{
	private:
		string username;
		string message;
		Tweet *tweets;
		int length;

		/* Prototypes */
		void addTweet(Tweet);
		void addTweet(Tweet, int);
		int calcSegments();
		int rGetLastPuncPos(int);
		void splitTweets();

	public:
		/* Constructors */
		TwitterManager()
		{
			username = "";
			message = "";
			tweets = new Tweet[100];
			length = 0;
		}

		TwitterManager(string name, string msg)
		{
			username = name;
			message = msg;
			tweets = new Tweet[100];
			length = 0;
			
			splitTweets();
		}

		/* Getters */
		string getUsername()
		{
			return username;
		}

		int getLength()
		{
			return length;
		}

		/* Setters */
		void setUsername(string newUsername)
		{
			username = newUsername;
		}

		void setMessage(string newMessage)
		{
			message = newMessage;
			splitTweets();
		}
		
		/* Prototypes */
		void display();

		/* Destructor */
		~TwitterManager()
		{
			delete[] tweets;
			tweets = NULL;
		}
};
 
#endif
