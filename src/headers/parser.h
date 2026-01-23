
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

using namespace std;


string parseFirstWord(string input);

/**
 * takes input, parse it according to number of args needed and returns the rest as the last argument
 */
vector<string> parseInput(string input, int numberOfArgs);


#endif

