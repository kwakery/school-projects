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

string generate_string(int max_length){
  string possible_characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  random_device rd;
  mt19937 engine(rd());
  uniform_int_distribution<> dist(0, possible_characters.size()-1);
  string ret = "";
  for(int i = 0; i < max_length; i++){
      int random_index = dist(engine); //get index between 0 and possible_characters.size()-1
      ret += possible_characters[random_index];
  }
  return ret;
}

TEST_CASE("Tweet", "[tweet]")
{
  srand(time(NULL));
  SECTION("Tweet creation")
  {
    Tweet t;
    CHECK(true == true);
  }
  SECTION("Getters design")
  {
    Tweet t;
    t.getUsername();
    t.getMessage();
    t.getCharLength();
    CHECK(true == true);
  }
  SECTION("Setters design")
  {
    Tweet t;
    t.setUsername("paul");
    t.setMessage("hello");
    CHECK(true == true);
  }
  SECTION("Getters and setters implementation")
  {
    for(int i = 0; i < 10; i++)
    {
      Tweet t;
      string username = generate_string(rand()%15);
      string message = generate_string(rand()%280);
      t.setUsername(username);
      t.setMessage(message);
      CHECK(t.getUsername() == username);
      CHECK(t.getMessage() == message);
      CHECK(t.getCharLength() == message.length());
    }
  }
  SECTION("Default constructor")
  {
    Tweet t;
    CHECK(t.getUsername() == "");
    CHECK(t.getMessage() == "");
    CHECK(t.getCharLength() == 0);
  }
  SECTION("Constructor overload")
  {
    for(int i = 0; i < 10; i++)
    {
      string username = generate_string(rand()%15);
      string message = generate_string(rand()%280);
      Tweet t(username, message);
      CHECK(t.getUsername() == username);
      CHECK(t.getMessage() == message);
      CHECK(t.getCharLength() == message.length());
    }
  }
  SECTION("Display")
  {
    for(int i = 0; i < 10; i++)
    {
      string username = generate_string(rand()%15);
      string message = generate_string(rand()%280);
      Tweet t(username, message);
      string output = func_str_out([&](){
        t.display();
      });
      string expected = "@" + username + ": " + message + "\n";
      CHECK(output == expected);
    }
  }
}

TEST_CASE("MultiTweet", "[mtweet]")
{
  srand(time(NULL));
  string loremipsum = "Lorem ipsum dolor sit amet commune concertationesque detracto ea electis maximi memoriter vetuit. Aliquip corrupte incurrunt odioque sentiunt, terminari urbane voluptate. Aegritudo aetatis animos consentientis, gessisse imitarentur incommoda percipit perdiscere quantaque scriptorem tation usu videor videro! Animadversionis consuevit cuius efficit, frui investigandi multos nisl nivem perinde reperire texit! Auctori cohaerescant deseruisse difficiles inanitate, inciderint intellegaturque invenerit putent recta sapientiam situm! Claudicare elaboraret explicatis fermentum, illius iure poetis probarem, rationem tertium utilitatibus. Debet ego eumque facilius fortitudo impediente maestitiam partes porrecta praeterierunt putet triarium. Dissident dixeris ingenii libenter malo, perspici probo triario vi? Animo commodius eiusdem evertunt his libido momenti nivem nostras optio plerique servare stabilitas vicinum. Desideret deterritum didicisset grate omnisque summumque terentianus. Alios contemnere habemus labefactetur maximeque opinemur pharetra usus viveremus. Chorusque coniuncta latine multis opus, plura praeter quisquam stoicos studium vellem! Amputata class disciplinae oritur, parentes probaretur suspendisse vester? Consilio dedecora foedus laetitiam leviora locum locus maledici omnia omnium peccandi penatibus praesidia voluerint! Accusantibus dicturam omnibus pellentesque veniam. Bonas bonorum dolores duo gravissimas, intervalla misisti multis referuntur sine. Atqui captiosa dedocere democritum, dis honesto ipsum naturae philosophiae ponderum probabo seiungi ulla! Acutus aiebat consequentium consoletur, is novi possimus sodales tertio! Attento certamen copulationesque data, ferentur fit fonte horum iudicium metum quamvis sermone sua ullius? Amori eae gaudeat istae option, senectutem sollicitant! Manilium platonis sinat soliditatem stoici. Accusantium attento cognoscerem elaboraret euismod, evertunt ferri impendet infanti intemperantes ornatum perspicuum referenda servire verterunt?";
  int len = loremipsum.length();

  SECTION("Object creation")
  {
    MultiTweet mt("","");
    CHECK(true == true);
  }
  SECTION("Inheritance")
  {
    MultiTweet mt("","");
    mt.getUsername();
    mt.getMessage();
    mt.getCharLength();
    mt.setUsername("");
    mt.setMessage("");
    CHECK(true==true);
  }
  SECTION("Getters design")
  {
    MultiTweet mt("","");
    mt.getSize();
    CHECK(true == true);
  }
  SECTION("Setters design")
  {
    MultiTweet mt("", "");
    mt.setMessage("");
    CHECK(true == true);
  }
  SECTION("Constructor overload")
  {
    for(int i = 0; i < 10; i++)
    {
      string username = generate_string(rand()%15);
      string message = generate_string(rand()%280+10);
      MultiTweet mt(username, message);
      CHECK(mt.getUsername() == username);
      CHECK(mt.getMessage() == message);
      CHECK(mt.getSize() > 0);
    }
  }

  SECTION("More than 280 characters, split on space")
  {
    for(int i = 0; i < 10; i++)
    {
      int beginRange = rand() % len/3 + 274;
      int spaceLoc = loremipsum.find(" ", beginRange);
      string message = loremipsum.substr(spaceLoc - 273, 380 + (rand() % 100)); 
      string first = message.substr(0, 274);
      string second = message.substr(274, message.length());
      string username = generate_string(rand()%15);
      
      MultiTweet mt(username, message);
      string output = func_str_out([&](){
        mt.display();
      });

      string expected = "@" + username + ": " + first + " (1/2)\n";
      expected += ("@" + username + ": " + second + " (2/2)\n");

      CHECK(mt.getSize() == 2);
      CHECK(output == expected);
    }
  }
  SECTION("More than 280 characters, split on .")
  {
    for(int i = 0; i < 10; i++)
    {
      int beginRange = rand() % len/3 + 274;
      int spaceLoc = loremipsum.find(".", beginRange);
      string message = loremipsum.substr(spaceLoc - 273, 380 + (rand() % 100)); 
      string first = message.substr(0, 274);
      string second = message.substr(274, message.length());
      string username = generate_string(rand()%15);
      
      MultiTweet mt(username, message);
      string output = func_str_out([&](){
        mt.display();
      });

      string expected = "@" + username + ": " + first + " (1/2)\n";
      expected += ("@" + username + ": " + second + " (2/2)\n");

      CHECK(mt.getSize() == 2);
      CHECK(output == expected);
    }
  }
  SECTION("More than 280 characters, split on ,")
  {
    for(int i = 0; i < 10; i++)
    {
      int beginRange = rand() % len/3 + 274;
      int spaceLoc = loremipsum.find(",", beginRange);
      string message = loremipsum.substr(spaceLoc - 273, 380 + (rand() % 100)); 
      string first = message.substr(0, 274);
      string second = message.substr(274, message.length());
      string username = generate_string(rand()%15);
      
      MultiTweet mt(username, message);
      string output = func_str_out([&](){
        mt.display();
      });

      string expected = "@" + username + ": " + first + " (1/2)\n";
      expected += ("@" + username + ": " + second + " (2/2)\n");

      CHECK(mt.getSize() == 2);
      CHECK(output == expected);
    }
  }
  SECTION("More than 280 characters, split on ?")
  {
    for(int i = 0; i < 10; i++)
    {
      int beginRange = rand() % len/3 + 274;
      int spaceLoc = loremipsum.find("?", beginRange);
      string message = loremipsum.substr(spaceLoc - 273, 380 + (rand() % 100)); 
      string first = message.substr(0, 274);
      string second = message.substr(274, message.length());
      string username = generate_string(rand()%15);
      
      MultiTweet mt(username, message);
      string output = func_str_out([&](){
        mt.display();
      });

      string expected = "@" + username + ": " + first + " (1/2)\n";
      expected += ("@" + username + ": " + second + " (2/2)\n");

      CHECK(mt.getSize() == 2);
      CHECK(output == expected);
    }
  }
  SECTION("More than 280 characters, split on !")
  {
    for(int i = 0; i < 10; i++)
    {
      int beginRange = rand() % len/3 + 274;
      int spaceLoc = loremipsum.find("!", beginRange);
      string message = loremipsum.substr(spaceLoc - 273, 380 + (rand() % 100)); 
      string first = message.substr(0, 274);
      string second = message.substr(274, message.length());
      string username = generate_string(rand()%15);
      
      MultiTweet mt(username, message);
      string output = func_str_out([&](){
        mt.display();
      });

      string expected = "@" + username + ": " + first + " (1/2)\n";
      expected += ("@" + username + ": " + second + " (2/2)\n");

      CHECK(mt.getSize() == 2);
      CHECK(output == expected);
    }
  }
  SECTION("More than 280 characters, split on non-space or punctuation character")
  {
    for(int i = 0; i < 10; i++)
    {
      int charLoc = -1;
      do
      {
        int temp = rand() % len/3 + 274;
        charLoc = temp + 273;
      }while(loremipsum.at(charLoc)== ' ' || loremipsum.at(charLoc)== ',' || loremipsum.at(charLoc)== ';' || loremipsum.at(charLoc)== '.' || loremipsum.at(charLoc)== '-' || loremipsum.at(charLoc)== '!' || loremipsum.at(charLoc)== '?');
      
      string message = loremipsum.substr(charLoc - 273, 380 + (rand() % 100));
      int splitPos = message.rfind(" ", 273);
      int tempPos = message.rfind(".", 273);
      splitPos = tempPos > splitPos ? tempPos : splitPos;
      tempPos = message.rfind("!", 273);
      splitPos = tempPos > splitPos ? tempPos : splitPos;
      tempPos = message.rfind("?", 273);
      splitPos = tempPos > splitPos ? tempPos : splitPos;
      tempPos = message.rfind(",", 273);
      splitPos = tempPos > splitPos ? tempPos : splitPos;
      tempPos = message.rfind(";", 273);
      splitPos = tempPos > splitPos ? tempPos : splitPos;
      tempPos = message.rfind("-", 273);
      splitPos = tempPos > splitPos ? tempPos : splitPos;

      string first = message.substr(0, splitPos+1);
      string second = message.substr(splitPos+1, message.length());

      string username = generate_string(rand()%15);
      
      MultiTweet mt(username, message);
      string output = func_str_out([&](){
        mt.display();
      });

      string expected = "@" + username + ": " + first + " (1/2)\n";
      expected += ("@" + username + ": " + second + " (2/2)\n");

      CHECK(mt.getSize() == 2);
      CHECK(output == expected);
    }
  }
  SECTION("More than 280 characters, no splits")
  {
    for(int i = 0; i < 10; i++)
    {
      string username = generate_string(rand()%15);
      string message = generate_string(400);
      string first = message.substr(0, 274);
      string second = message.substr(274, message.length());
      
      MultiTweet mt(username, message);
      string output = func_str_out([&](){
        mt.display();
      });

      string expected = "@" + username + ": " + first + " (1/2)\n";
      expected += ("@" + username + ": " + second + " (2/2)\n");

      CHECK(mt.getSize() == 2);
      CHECK(output == expected);
    }
  }
  SECTION("Greater than 560 characters")
  {
    for(int j = 0; j < 10; j++)
    {
      char symbols[7] = {' ', ',', ';', '-', '.', '!', '?'};
      int splits = rand() % 8 + 3;
      string *splitStrings = new string[splits];
      string message = "";
      for(int i = 0; i < splits; i++)
      {
        int beginRange = rand() % len/3 + 274;
        int symbol = -1;        
        int charLoc = -1;
        while(charLoc == -1)
        {
          symbol = rand() % 8;
          charLoc = loremipsum.find(symbols[symbol], beginRange);
        }

        splitStrings[i] = loremipsum.substr(charLoc - 273, 274); 
        message += splitStrings[i];
      }

      string username = generate_string(rand()%15);      
      MultiTweet mt(username, message);
      string output = func_str_out([&](){
        mt.display();
      });
      CHECK(mt.getSize() == splits);
      string expected = "";
      for(int i = 0; i < splits; i++)
      {
        expected+= ("@" + username + ": " + splitStrings[i] + " (" + to_string(i+1) + "/" + to_string(splits) + ")\n");
      }
      CHECK(output == expected);
    }
  }
}

TEST_CASE("TweetStream", "[tstream]")
{
  srand(time(NULL));
  string loremipsum = "Lorem ipsum dolor sit amet commune concertationesque detracto ea electis maximi memoriter vetuit. Aliquip corrupte incurrunt odioque sentiunt, terminari urbane voluptate. Aegritudo aetatis animos consentientis, gessisse imitarentur incommoda percipit perdiscere quantaque scriptorem tation usu videor videro! Animadversionis consuevit cuius efficit, frui investigandi multos nisl nivem perinde reperire texit! Auctori cohaerescant deseruisse difficiles inanitate, inciderint intellegaturque invenerit putent recta sapientiam situm! Claudicare elaboraret explicatis fermentum, illius iure poetis probarem, rationem tertium utilitatibus. Debet ego eumque facilius fortitudo impediente maestitiam partes porrecta praeterierunt putet triarium. Dissident dixeris ingenii libenter malo, perspici probo triario vi? Animo commodius eiusdem evertunt his libido momenti nivem nostras optio plerique servare stabilitas vicinum. Desideret deterritum didicisset grate omnisque summumque terentianus. Alios contemnere habemus labefactetur maximeque opinemur pharetra usus viveremus. Chorusque coniuncta latine multis opus, plura praeter quisquam stoicos studium vellem! Amputata class disciplinae oritur, parentes probaretur suspendisse vester? Consilio dedecora foedus laetitiam leviora locum locus maledici omnia omnium peccandi penatibus praesidia voluerint! Accusantibus dicturam omnibus pellentesque veniam. Bonas bonorum dolores duo gravissimas, intervalla misisti multis referuntur sine. Atqui captiosa dedocere democritum, dis honesto ipsum naturae philosophiae ponderum probabo seiungi ulla! Acutus aiebat consequentium consoletur, is novi possimus sodales tertio! Attento certamen copulationesque data, ferentur fit fonte horum iudicium metum quamvis sermone sua ullius? Amori eae gaudeat istae option, senectutem sollicitant! Manilium platonis sinat soliditatem stoici. Accusantium attento cognoscerem elaboraret euismod, evertunt ferri impendet infanti intemperantes ornatum perspicuum referenda servire verterunt?";
  int len = loremipsum.length();

  SECTION("Object creation")
  {
    TweetStream ts(generate_string(rand()%5));
    CHECK(true == true);
  }
  SECTION("Getters design")
  {
    TweetStream ts(generate_string(rand()%5));
    ts.getUsername();
    ts.getSize();
    CHECK(true == true);
  }
  SECTION("Setters design")
  {
    TweetStream ts(generate_string(rand()%5));
    ts.setUsername("paul");
    ts.addMessage("hello");
    CHECK(true == true);
  }
  SECTION("Getters and setters implementation")
  {
    for(int i = 0; i < 10; i++)
    {
      TweetStream ts(generate_string(rand()%5));
      string username = generate_string(rand()%15);
      string message = generate_string(rand()%280);
      ts.setUsername(username);
      ts.addMessage(message);
      CHECK(ts.getUsername() == username);
    }
  }
  SECTION("Constructor overload")
  {
    for(int i = 0; i < 10; i++)
    {
      string username = generate_string(rand()%15);
      string message = generate_string(rand()%280);
      TweetStream ts(username);
      CHECK(ts.getUsername() == username);
    }
  }
  SECTION("Constructor and Tweet splitting implementation - less than 280")
  {
    for(int i = 0; i < 10; i++)
    {
      string username = generate_string(rand()%15);
      string message = generate_string(rand()%280);
      TweetStream ts(username);
      ts.addMessage(message);
      string output = func_str_out([&](){
        ts.display();
      });
      string expected = "@" + username + ": " + message + "\n";
      CHECK(ts.getSize() == 1);
      CHECK(output == expected);
    }
  }
  SECTION("setMessage and Tweet splitting implementation - less than 280")
  {
    for(int i = 0; i < 10; i++)
    {
      string username = generate_string(rand()%15);
      string message = generate_string(rand()%280);
      TweetStream ts(generate_string(rand()%5));
      ts.setUsername(username);
      ts.addMessage(message);
      string output = func_str_out([&](){
        ts.display();
      });
      string expected = "@" + username + ": " + message + "\n";
      CHECK(ts.getSize() == 1);
      CHECK(output == expected);
    }
  }
  SECTION("More than 280 characters, split on space")
  {
    for(int i = 0; i < 10; i++)
    {
      int beginRange = rand() % len/3 + 274;
      int spaceLoc = loremipsum.find(" ", beginRange);
      string message = loremipsum.substr(spaceLoc - 273, 380 + (rand() % 100)); 
      string first = message.substr(0, 274);
      string second = message.substr(274, message.length());
      string username = generate_string(rand()%15);
      
      TweetStream ts(username);
      ts.addMessage(message);
      string output = func_str_out([&](){
        ts.display();
      });

      string expected = "@" + username + ": " + first + " (1/2)\n";
      expected += ("@" + username + ": " + second + " (2/2)\n");

      CHECK(ts.getSize() == 1);
      CHECK(output == expected);
    }
  }
  SECTION("More than 280 characters, split on .")
  {
    for(int i = 0; i < 10; i++)
    {
      int beginRange = rand() % len/3 + 274;
      int spaceLoc = loremipsum.find(".", beginRange);
      string message = loremipsum.substr(spaceLoc - 273, 380 + (rand() % 100)); 
      string first = message.substr(0, 274);
      string second = message.substr(274, message.length());
      string username = generate_string(rand()%15);
      
      TweetStream ts(username);
      ts.addMessage(message);
      string output = func_str_out([&](){
        ts.display();
      });

      string expected = "@" + username + ": " + first + " (1/2)\n";
      expected += ("@" + username + ": " + second + " (2/2)\n");

      CHECK(ts.getSize() == 1);
      CHECK(output == expected);
    }
  }
  SECTION("More than 280 characters, split on ?")
  {
    for(int i = 0; i < 10; i++)
    {
      int beginRange = rand() % len/3 + 274;
      int spaceLoc = loremipsum.find("?", beginRange);
      string message = loremipsum.substr(spaceLoc - 273, 380 + (rand() % 100)); 
      string first = message.substr(0, 274);
      string second = message.substr(274, message.length());
      string username = generate_string(rand()%15);
      
      TweetStream ts(username);
      ts.addMessage(message);
      string output = func_str_out([&](){
        ts.display();
      });

      string expected = "@" + username + ": " + first + " (1/2)\n";
      expected += ("@" + username + ": " + second + " (2/2)\n");

      CHECK(ts.getSize() == 1);
      CHECK(output == expected);
    }
  }
  SECTION("More than 280 characters, split on !")
  {
    for(int i = 0; i < 10; i++)
    {
      int beginRange = rand() % len/3 + 274;
      int spaceLoc = loremipsum.find("!", beginRange);
      string message = loremipsum.substr(spaceLoc - 273, 380 + (rand() % 100)); 
      string first = message.substr(0, 274);
      string second = message.substr(274, message.length());
      string username = generate_string(rand()%15);
      
      TweetStream ts(username);
      ts.addMessage(message);
      string output = func_str_out([&](){
        ts.display();
      });

      string expected = "@" + username + ": " + first + " (1/2)\n";
      expected += ("@" + username + ": " + second + " (2/2)\n");

      CHECK(ts.getSize() == 1);
      CHECK(output == expected);
    }
  }
  SECTION("More than 280 characters, split on non-space or punctuation character")
  {
    for(int i = 0; i < 10; i++)
    {
      int charLoc = -1;
      do
      {
        int temp = rand() % len/3 + 274;
        charLoc = temp + 273;
      }while(loremipsum.at(charLoc)== ' ' || loremipsum.at(charLoc)== ',' || loremipsum.at(charLoc)== ';' || loremipsum.at(charLoc)== '.' || loremipsum.at(charLoc)== '-' || loremipsum.at(charLoc)== '!' || loremipsum.at(charLoc)== '?');
      
      string message = loremipsum.substr(charLoc - 273, 380 + (rand() % 100));
      int splitPos = message.rfind(" ", 273);
      int tempPos = message.rfind(".", 273);
      splitPos = tempPos > splitPos ? tempPos : splitPos;
      tempPos = message.rfind("!", 273);
      splitPos = tempPos > splitPos ? tempPos : splitPos;
      tempPos = message.rfind("?", 273);
      splitPos = tempPos > splitPos ? tempPos : splitPos;
      tempPos = message.rfind(",", 273);
      splitPos = tempPos > splitPos ? tempPos : splitPos;
      tempPos = message.rfind(";", 273);
      splitPos = tempPos > splitPos ? tempPos : splitPos;
      tempPos = message.rfind("-", 273);
      splitPos = tempPos > splitPos ? tempPos : splitPos;




      string first = message.substr(0, splitPos+1);
      string second = message.substr(splitPos+1, message.length());

      string username = generate_string(rand()%15);
      
      TweetStream ts(username);
      ts.addMessage(message);
      string output = func_str_out([&](){
        ts.display();
      });

      string expected = "@" + username + ": " + first + " (1/2)\n";
      expected += ("@" + username + ": " + second + " (2/2)\n");

      CHECK(ts.getSize() == 1);
      CHECK(output == expected);
    }
  }
  SECTION("More than 280 characters, no splits")
  {
    for(int i = 0; i < 10; i++)
    {
      string username = generate_string(rand()%15);
      string message = generate_string(400);
      string first = message.substr(0, 274);
      string second = message.substr(274, message.length());
      
      TweetStream ts(username);
      ts.addMessage(message);
      string output = func_str_out([&](){
        ts.display();
      });

      string expected = "@" + username + ": " + first + " (1/2)\n";
      expected += ("@" + username + ": " + second + " (2/2)\n");

      CHECK(ts.getSize() == 1);
      CHECK(output == expected);
    }
  }
  SECTION("Greater than 560 characters")
  {
    for(int j = 0; j < 10; j++)
    {
      char symbols[7] = {' ', ',', ';', '-', '.', '!', '?'};
      int splits = rand() % 8 + 3;
      string *splitStrings = new string[splits];
      string message = "";
      for(int i = 0; i < splits; i++)
      {
        int beginRange = rand() % len/3 + 274;
        int symbol = -1;        
        int charLoc = -1;
        while(charLoc == -1)
        {
          symbol = rand() % 8;
          charLoc = loremipsum.find(symbols[symbol], beginRange);
        }

        splitStrings[i] = loremipsum.substr(charLoc - 273, 274); 
        message += splitStrings[i];
      }

      string username = generate_string(rand()%15);      
      TweetStream ts(username);
      ts.addMessage(message);
      string output = func_str_out([&](){
        ts.display();
      });
      CHECK(ts.getSize() == 1);
      string expected = "";
      for(int i = 0; i < splits; i++)
      {
        expected+= ("@" + username + ": " + splitStrings[i] + " (" + to_string(i+1) + "/" + to_string(splits) + ")\n");
      }
      CHECK(output == expected);
    }
  }
}