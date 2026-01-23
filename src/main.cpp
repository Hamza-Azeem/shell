#include <iostream>
#include <string>
#include <vector>
#include "headers/constants.h"
#include <cstdlib>
#include "headers/type.h"
#include <unistd.h>
#include <sys/wait.h>
#include "headers/parser.h"

using namespace std;

// vector<string> parseInput(string input)
// {
//   vector<string> result;
//   string word = "";
//   int count = 0;
//   for (int i = 0; i < input.size(); i++)
//   {
//     if (input[i] == ' ' && count == 0)
//     {
//       result.push_back(word);
//       word = "";
//     }
//     else if (input[i] == '"')
//     {
//       word += '"';
//       count++;
//       if (count == 2)
//       {
//         result.push_back(word);
//         word = "";
//         count = 0;
//       }
//     }
//     else
//     {
//       word += input[i];
//     }
//   }
//   if (!word.empty())
//   {
//     result.push_back(word);
//   }

//   return result;
// }

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
    string firstWord = parseFirstWord(input);
    if (firstWord == "echo")
    {
      vector<string> parsedLine = parseInput(input.substr(firstWord.size() + 1), 1);
      for(int i=0;i<parsedLine.size();i++){
        cout << parsedLine[i] << " ";
      }
      cout << "\n";
    }
    else if (firstWord == "type")
    {
      vector<string> parsedLine = parseInput(input.substr(firstWord.size() + 1), 1);
      string result = checkType(PATH, parsedLine[0]);
      if (result != "")
      {
        cout << parsedLine[0] << " is " << result << "\n";
      }
      else
      {
        cout << parsedLine[0] << ": not found\n";
      }
    }
    else if (firstWord == "exit")
    {
      break;
    }
    else
    {
      string result = checkType(PATH, firstWord);
      if (result != "" && result != "a shell builtin")
      {
        pid_t pid = fork();
        if (pid == -1)
        {
          perror("fork failed");
        }
        else if (pid == 0)
        {
          vector<char *> c_args;
          c_args.push_back(const_cast<char *>(firstWord.c_str()));
          vector<string> parsedLine = parseInput(input.substr(firstWord.size()+1), -1);
          // for(int i=0;i<parsedLine.size();i++){
          //   cout << parsedLine[i] << " ";
          // }
          cout << endl;
          if (parsedLine.size() >= 1)
          {
            for (auto it = parsedLine.begin(); it != parsedLine.end(); ++it)
            {
              c_args.push_back(const_cast<char *>(it->c_str()));
            }
          }
          c_args.push_back(nullptr);
          execv(result.c_str(), c_args.data());
          // If we get here, it failed
          perror("execv failed");
          _exit(1);
        }
        else
        {
          int status;
          waitpid(pid, &status, 0);
        }
      }
    }
  }
}
