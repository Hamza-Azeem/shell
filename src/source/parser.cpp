#include <string>
#include <vector>
#include <iostream>

using namespace std;

string parseFirstWord(string input)
{
    string word = "";
    for (int i = 0; i < input.size(); i++)
    {
        if(input[i] == ' '){
            break;
        }else{
            word+=input[i];
        }
    }
    return word;
}

/**
 * takes input, parse it according to number of args needed and returns the rest as the last argument
 * -1 to parse every word as an argument
 * words are separated by 'space'
 */
void addRestOfLine(vector<string> &parsed, string input, int index);
vector<string> parseInput(string input, int numberOfArgs)
{
    vector<string> result;
    string word = "";
    int quotesFlag = 0;
    int argsParsed = 0;
    int index = 0;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == ' ' && quotesFlag == 0)
        {
            result.push_back(word);
            word = "";
            argsParsed++;
        }
        else if (input[i] == '"')
        {
            word += '"';
            quotesFlag++;
            if (quotesFlag == 2)
            {
                result.push_back(word);
                word = "";
                quotesFlag = 0;
                argsParsed++;
            }
        }
        else
        {
            word += input[i];
        }
        if (argsParsed == numberOfArgs)
        {
            index = i + 1;
            break;
        }
    }
    if (!word.empty())
    {
        result.push_back(word);
    }
    if (index != input.size() && index != 0)
    {
        addRestOfLine(result, input, index);
    }
    return result;
}

void addRestOfLine(vector<string> &parsed, string input, int index)
{
    string last = "";
    for (int i = index; i < input.size(); i++)
    {
        last += input[i];
    }
    parsed.push_back(last);
}