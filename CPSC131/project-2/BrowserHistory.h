#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdexcept>
#include "Webpage.h"
using namespace std;

class BrowserHistory {
public:
    BrowserHistory();

    void visitSite(Webpage newSite);
    string back();
    string forward();

    void readHistory(string fileName);

    string getUrl();
    size_t getNavSize();
    list<Webpage> getSitesVisited();

private:
    list<Webpage> navHistory; // List of history
    list<Webpage>::iterator navPos; // Iterator for navHistory
    list<Webpage> sitesVisited; // List of sites visited overall
    int numSites;
};

/**
 * Default Constructor
 */
BrowserHistory::BrowserHistory()
{
    navPos = navHistory.begin(); // Initialize iterator for navHistory
}

/**
 * Visits the site and adds to history
 * If the back button is pressed and then the user navigates to another url, forward history is deleted
 */
void BrowserHistory::visitSite(Webpage newSite)
{
    /* back() -> visitSite() */
    while (navPos != --navHistory.end()) // Run loop as long as the iterator isn't considered to be at the end
    {
        navHistory.pop_back(); // Delete last element in the history list
    }

    /* Add webpage to lists */
    navHistory.push_back(newSite);
    sitesVisited.push_back(newSite);

    navPos = --navHistory.end(); // Start iterator on last element
}

/**
 * Navigates back to last page
 * @return - url of the updated page
 */
string BrowserHistory::back()
{
    navPos--; // Go to previous page of history

    return getUrl();
}

/**
 * Navigates to the next page in history
 * @return - url of the updated page
 */
string BrowserHistory::forward()
{
    navPos++; // Go to newer page of history

    return getUrl();
}

/* Reads through file as user input
 * Each time "new" appears, browser will parse as url and time and visit it
 * Each time "back" appears, browser will go back to last page
 * Each time "forward" appears, browser will go forward to the more recent page viewed
 */
void BrowserHistory::readHistory(string fileName) {
    string temp;
    int newTime;
    Webpage newSite;
    ifstream inFile(fileName.c_str());

    while(inFile >> temp) {
        if(temp == "new") {
            inFile >> temp >> newTime;
            newSite = Webpage(temp, time_t(newTime));
            visitSite(newSite);
        } else if(temp == "back") {
            back();
        } else if(temp == "forward") {
            forward();
        } else {
            throw logic_error("invalid command");
        }
    }
}

/**
 * Gets the current url the user is on
 * @return - url of the webpage the iterator is on
 */
string BrowserHistory::getUrl()
{
    if (navHistory.empty()) // Check if list is empty
        throw logic_error("History is empty.");

    return navPos->getUrl(); // Return the url of the iterator's current page
}

/**
 * Gets the number of sites visited
 * @return - number of sites visited
 */
size_t BrowserHistory::getNavSize()
{
    return navHistory.size();
}

/**
 * Get sites visited
 * @return - list of sites visited by the user
 */
list<Webpage> BrowserHistory::getSitesVisited()
{
    return sitesVisited;
}
