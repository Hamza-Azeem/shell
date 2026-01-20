#include <iostream>
#include <string>
#include <vector>
#include "headers/constants.h"
#include <cstdlib>
#include "headers/type.h"
#include <boost/process.hpp>

using namespace std;
namespace bp = boost::process;

vector<string> parseInput(string input)
{
  vector<string> result;
  string word = "";
  int count = 0;
  for (int i = 0; i < input.size(); i++)
  {
    if (input[i] == ' ' && count == 0)
    {
      result.push_back(word);
      word = "";
    }
    else if (input[i] == '"')
    {
      word += '"';
      count++;
      if (count == 2)
      {
        result.push_back(word);
        word = "";
        count = 0;
      }
    }
    else
    {
      word += input[i];
    }
  }
  if (!word.empty())
  {
    result.push_back(word);
  }

  return result;
}

int main()
{

  cout << unitbuf;
  cerr << unitbuf;
  const string PATH = getenv("PATH");
  while (true)
  {
    cout << "$ ";
    string input;
    getline(cin, input);
    vector<string> parsedLine = parseInput(input);
    string command = parsedLine[0];
    if (command == "echo")
    {
      cout << parsedLine[1] << "\n";
    }
    else if (command == "type")
    {
      string result = checkType(PATH, parsedLine[1]);
      if (result != "")
      {
        cout << parsedLine[1] << " is " << result << "\n";
      }
      else
      {
        cout << parsedLine[1] << ": not found\n";
      }
    }
    else if (command == "exit")
    {
      break;
    }
    else
    {
      string result = checkType(PATH, parsedLine[0]);
      if (result != "" && result != "a shell builtin")
      {
        vector<string> args;
        args.assign(parsedLine.begin() + 1, parsedLine.end());
        // cout << args.size() << endl;
        // for (int i = 0; i < args.size(); i++)
        //   cout << args[i] << " ";
        // cout << endl;
        bp::system(result, args);
      }
    }
  }
}
