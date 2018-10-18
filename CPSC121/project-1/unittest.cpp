/*
MIT License

Copyright (c) 2018 Paul Salvador Inventado

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "catch.hpp"
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "twitter.hpp"

#include <random>

using namespace std;

string couttest(string progName, string input)
{
  FILE *fp = popen(("echo \""+ input +"\" | ./" + progName).c_str(), "r");
  char buf[1024];
  string output = "";
  while (fgets(buf, 1024, fp)) {
    output += buf;
  }
  pclose(fp);  
  return output;
}

string to_string_double(double val, const int prec = 2)
{
    std::ostringstream out;
    out << fixed << setprecision(prec) << val;
    return out.str();
}

string func_str_out(function<void()> func)
{
  // code for capturing cout taken from
  // https://stackoverflow.com/questions/19485536/redirect-output-of-an-function-printing-to-console-to-string
  std::stringstream ss;
  auto old_buf = std::cout.rdbuf(ss.rdbuf()); 
  func();
  std::cout.rdbuf(old_buf);
  return ss.str();
}

TEST_CASE("splitTweet", "[splittweet]")
{
  srand(time(NULL));
  string loremipsum = "Lorem ipsum dolor sit amet commune concertationesque detracto ea electis maximi memoriter vetuit. Aliquip corrupte incurrunt odioque sentiunt, terminari urbane voluptate. Aegritudo aetatis animos consentientis, gessisse imitarentur incommoda percipit perdiscere quantaque scriptorem tation usu videor videro! Animadversionis consuevit cuius efficit, frui investigandi multos nisl nivem perinde reperire texit! Auctori cohaerescant deseruisse difficiles inanitate, inciderint intellegaturque invenerit putent recta sapientiam situm! Claudicare elaboraret explicatis fermentum, illius iure poetis probarem, rationem tertium utilitatibus. Debet ego eumque facilius fortitudo impediente maestitiam partes porrecta praeterierunt putet triarium. Dissident dixeris ingenii libenter malo, perspici probo triario vi? Animo commodius eiusdem evertunt his libido momenti nivem nostras optio plerique servare stabilitas vicinum. Desideret deterritum didicisset grate omnisque summumque terentianus. Alios contemnere habemus labefactetur maximeque opinemur pharetra usus viveremus. Chorusque coniuncta latine multis opus, plura praeter quisquam stoicos studium vellem! Amputata class disciplinae oritur, parentes probaretur suspendisse vester? Consilio dedecora foedus laetitiam leviora locum locus maledici omnia omnium peccandi penatibus praesidia voluerint! Accusantibus dicturam omnibus pellentesque veniam. Bonas bonorum dolores duo gravissimas, intervalla misisti multis referuntur sine. Atqui captiosa dedocere democritum, dis honesto ipsum naturae philosophiae ponderum probabo seiungi ulla! Acutus aiebat consequentium consoletur, is novi possimus sodales tertio! Attento certamen copulationesque data, ferentur fit fonte horum iudicium metum quamvis sermone sua ullius? Amori eae gaudeat istae option, senectutem sollicitant! Manilium platonis sinat soliditatem stoici. Accusantium attento cognoscerem elaboraret euismod, evertunt ferri impendet infanti intemperantes ornatum perspicuum referenda servire verterunt?";
  int len = loremipsum.length();

  SECTION("Less than 280 characters")
  {
    for(int i = 0; i < 10; i++)
    {
      int begin = rand() % (len-(len/2));
      string temp = loremipsum.substr(begin, len);
      string message = temp.substr(0, temp.rfind(" ", 279));
      string output[100] = {};
      int count = 0;
      splitTweets(message, output, &count);
      CHECK(count == 1);
      CHECK(output[0] == message);
    }
  }
  SECTION("More than 280 characters, split on space")
  {
    for(int i = 0; i < 10; i++)
    {
      int beginRange = rand() % len/3 + 280;
      int spaceLoc = loremipsum.find(" ", beginRange);
      string message = loremipsum.substr(spaceLoc - 279, 285 + (rand() % 100)); 
      string first = message.substr(0, 280);
      string second = message.substr(280, message.length());
      string output[100] = {};
      int count = 0;

      splitTweets(message, output, &count);
      CHECK(count == 2);
      CHECK(output[0] == first);
      CHECK(output[1] == second);
    }
  }
  SECTION("More than 280 characters, split on .")
  {
    for(int i = 0; i < 10; i++)
    {
      int beginRange = rand() % len/3 + 280;
      int spaceLoc = loremipsum.find(".", beginRange);
      string message = loremipsum.substr(spaceLoc - 279, 285 + (rand() % 100)); 
      string first = message.substr(0, 280);
      string second = message.substr(280, message.length());
      string output[100] = {};
      int count = 0;

      splitTweets(message, output, &count);
      CHECK(count == 2);
      CHECK(output[0] == first);
      CHECK(output[1] == second);
    }
  }
  SECTION("More than 280 characters, split on !")
  {
    for(int i = 0; i < 10; i++)
    {
      int beginRange = rand() % len/3 + 280;
      int spaceLoc = loremipsum.find("!", beginRange);
      string message = loremipsum.substr(spaceLoc - 279, 285 + (rand() % 100)); 
      string first = message.substr(0, 280);
      string second = message.substr(280, message.length());
      string output[100] = {};
      int count = 0;

      splitTweets(message, output, &count);
      CHECK(count == 2);
      CHECK(output[0] == first);
      CHECK(output[1] == second);
    }
  }
  SECTION("More than 280 characters, split on ?")
  {
    for(int i = 0; i < 10; i++)
    {
      int beginRange = rand() % len/3 + 280;
      int spaceLoc = loremipsum.find("?", beginRange);
      string message = loremipsum.substr(spaceLoc - 279, 285 + (rand() % 100)); 
      string first = message.substr(0, 280);
      string second = message.substr(280, message.length());
      string output[100]= {};
      int count = 0;

      splitTweets(message, output, &count);
      CHECK(count == 2);
      CHECK(output[0] == first);
      CHECK(output[1] == second);
    }
  }
  SECTION("More than 280 characters, split on non-space or punctuation character")
  {
    for(int i = 0; i < 10; i++)
    {
      int charLoc = -1;
      do
      {
        int temp = rand() % len/3 + 280;
        charLoc = temp + 279;
      }while(loremipsum.at(charLoc)== ' ' || loremipsum.at(charLoc)== '.' || loremipsum.at(charLoc)== '!' || loremipsum.at(charLoc)== '?');
      
      string message = loremipsum.substr(charLoc - 279, 285 + (rand() % 100));
      int splitPos = message.rfind(" ", 279);
      int tempPos = message.rfind(".", 279);
      splitPos = tempPos > splitPos ? tempPos : splitPos;
      tempPos = message.rfind("!", 279);
      splitPos = tempPos > splitPos ? tempPos : splitPos;
      tempPos = message.rfind("?", 279);
      splitPos = tempPos > splitPos ? tempPos : splitPos;

      string first = message.substr(0, splitPos+1);
      string second = message.substr(splitPos+1, message.length());
      string output[100] = {};
      int count = 0;

      splitTweets(message, output, &count);
      CHECK(count == 2);
      CHECK(output[0] == first);
      CHECK(output[1] == second);
    }
  }
  SECTION("Greater than 560 characters")
  {
    for(int j = 0; j < 10; j++)
    {
      char symbols[4] = {' ', '.', '!', '?'};
      int splits = rand() % 8 + 3;
      string *splitStrings = new string[splits];
      string message = "";
      for(int i = 0; i < splits; i++)
      {
        int symbol = rand() % 4;
        int beginRange = rand() % len/3 + 280;
        int charLoc = loremipsum.find(symbols[symbol], beginRange);
        splitStrings[i] = loremipsum.substr(charLoc - 279, 280); 
        message += splitStrings[i];
      }
      
      string output[100] = {};
      int count = 0;

      splitTweets(message, output, &count);
      REQUIRE(count == splits);
      for(int i = 0; i < splits; i++)
      {
        CHECK(output[i] == splitStrings[i]);  
      }
    }
  }
}

TEST_CASE("displaySplitTweet", "[displayst]")
{
  srand(time(NULL));
  string names[5] = {"Tony", "Bruce", "T'Challa", "Natasha", "Gamora"};
  string quotes[5][3] = {
    {
      "I told you. I don’t want to join your super-secret boy band.",
      "I’m a huge fan of the way you lose control and turn into an enormous green rage monster.",
      "Genius, billionaire, playboy, philanthropist."
    },
    {
      "Hulk smash!",
      "No Banner, only Hulk!",
      "But Hulk like real fire. Like... raging fire. Thor like smouldering fire."
    },
    {
      "If anyone found out what we truly are and what we possess, it could destroy the world. It is my duty to protect it.",
      "I did not yield! And as you can see, I am not dead! The challenge continues!",
      "Show them who we are."
    },
    {
      "I'm always picking up after you boys.",
      "Let's finish the job.",
      "Nothing lasts forever."
    },
    {
      "I have lived most my life surrounded by my enemies. I would be grateful to die among my friends.",
      "I'm a warrior and an assassin. I do not dance.",
      "Whatever nightmares the future holds are but dreams compared to what's behind me."
    }
  };

  SECTION("Array with no splits")
  {
    for(int i = 0; i < 10; i++)
    {
      int nidx = rand() % 5;
      int qidx = rand() % 3;
      string expected = "@" + names[nidx] + ": " + quotes[nidx][qidx] + "\n";
      string splits[1];
      splits[0] = quotes[nidx][qidx];    
      string output = func_str_out([&](){
        displaySplitTweet(splits, 1, names[nidx]);
      });
      CHECK(output == expected);
    }
  }
  SECTION("Array with 2 splits")
  {
    for(int i = 0; i < 10; i++)
    {
      int nidx = rand() % 5;
      int qidx1 = rand() % 3;
      int qidx2 = rand() % 3;
      string expected = "@" + names[nidx] + ": " + quotes[nidx][qidx1] + " (1/2)\n";
      expected+= "@" + names[nidx] + ": " + quotes[nidx][qidx2] + " (2/2)\n";
      string splits[2];
      splits[0] = quotes[nidx][qidx1];    
      splits[1] = quotes[nidx][qidx2];    
      string output = func_str_out([&](){
        displaySplitTweet(splits, 2, names[nidx]);
      });
      CHECK(output == expected);
    }
  }
  SECTION("Array with multiple splits")
  {
    for(int i = 0; i < 10; i++)
    {
      int nidx = rand() % 5;
      string expected = "@" + names[nidx] + ": " + quotes[nidx][0] + " (1/3)\n";
      expected+= "@" + names[nidx] + ": " + quotes[nidx][1] + " (2/3)\n";
      expected+= "@" + names[nidx] + ": " + quotes[nidx][2] + " (3/3)\n";
      string splits[3];
      for(int j = 0; j < 3; j++)
      {
        splits[j] = quotes[nidx][j];
      }
      string output = func_str_out([&](){
        displaySplitTweet(splits, 3, names[nidx]);
      });
      CHECK(output == expected);
    }
  }
}
