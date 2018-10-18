#ifndef TWITTER_HPP
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
		virtual void display();
};

class MultiTweet : public Tweet
{
	private:
		string *subMessages; // Stores the splits of the original messages
		int size; // # of sub messages
		
	public:
		/* Constructors */
		MultiTweet(string newUsername, string newMessage) : Tweet(newUsername, newMessage)
		{
			subMessages = new string[100];
			size = 0;
			splitTweets();
		}

		/* Getters */
		int getSize()
		{
			return size;
		}
		
		/* Prototypes */
		int calcSegments();
		int rGetLastPuncPos(int);
		void splitTweets();
		virtual void display();
};

/* Responsible for receiving messages & displaying all Tweets */
class TweetStream
{
    private:
        string username; // Sender of messages
        Tweet *tweets[100]; // array capable of holding both Tweet and MultiTweet objects
        int size; // Keeps track of how many messages have been set
    public:
        /* Constructors */
        TweetStream(string newUsername)
        {
            username = newUsername;
            size = 0;
        }
        
        /* Getters */
        string getUsername()
        {
            return username;
        }
        int getSize()
        {
            return size;
        }
        
        /* Setters */
        void setUsername(string newUsername)
        {
            username = newUsername;
        }

        /* Prototypes */
        bool addMessage(string);
        void display(); 
};
 
#endif
