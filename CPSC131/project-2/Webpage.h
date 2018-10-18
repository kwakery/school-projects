#pragma once

#include <string>
using namespace std;

class Webpage {
public:
    Webpage();
    Webpage(const string&, const time_t&);
    string getUrl();
    time_t getTime();

private:
    string url; // url of the site
    time_t timeStamp; // time user visited site
};

/**
 * Default Constructor
 */
Webpage::Webpage()
{
    url = "";
    timeStamp = 0;
}

/**
 * Constructor
 * @param webPageUrl - the url of the webpage visited
 * @param timeVisited - the time the webpage was visited
 */
Webpage::Webpage(const string& webpageUrl, const time_t& timeVisited)
{
    url = webpageUrl;
    timeStamp = timeVisited;
}

/**
 * Gets the webpage's url
 * @return - url of the webpage
 */
string Webpage::getUrl()
{
    return url;
}

/**
 * Gets the webpage's time
 * @return - time the webpage was visited
 */
time_t Webpage::getTime()
{
    return timeStamp;
}
