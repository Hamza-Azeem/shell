#include <iostream>
#include <string>
#include <vector>
#include "headers/constants.hpp"
using namespace std;

vector<string> parseInput(string input)
{
  vector<string> result;
  string command = "";
  int index = 0;
  for (int i = 0; i < input.size(); i++)
  {
    if (input[i] == ' ')
    {
      result.push_back(command);
      index = i + 1;
      break;
    }
    command += input[i];
  }
  string rest = "";
  for (int i = index; i < input.size(); i++)
  {
    rest += input[i];
  }
  result.push_back(rest);
  return result;
}

int main()
{

  cout << unitbuf;
  cerr << unitbuf;
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
      int c = BUILTIN_COMMANDS.count(parsedLine[1]);
      if(c > 0){
        cout << parsedLine[1] << " is a shell builtin\n";
      }else{
        cout << parsedLine[1] << ": " << "not found\n";
      }
    }
    else if (command == "exit")
    {
      break;
    }
    else
    {
      cout << input << ": command not found \n";
    }
  }
}
