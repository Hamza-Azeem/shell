#include "../headers/type.h"
#include <string>
#include "../headers/constants.h"
#include <iostream>
#include "../headers/files.h"
using namespace std;




string checkType(string PATH, string generic)
{
    int c = BUILTIN_COMMANDS.count(generic);
    if (c > 0)
    {
        return "a shell builtin"; // for regular commands
    }
    // maybe an executable file -- look for it in $PATH
    string currentDiretory = "";
    for (int i = 0; i < PATH.size(); i++)
    {
        if (PATH[i] == ':' || PATH[i] == ';')
        {
            // call function
            string result = getFilePath(currentDiretory, generic);
            if(result  != "") return result;  // file found and executable
            currentDiretory = "";
        }
        else
        {
            currentDiretory += PATH[i];
        }
    }
    // not recongnized
    return "";
}

