#include "../headers/type.h"
#include <filesystem>
#include <string>
#include "../headers/constants.h"
#include <iostream>
namespace fs = std::filesystem;
using namespace std;


string getFilePath(string driectory, string filename)
{
    if (fs::exists(driectory))
    {
        for (const auto &entry : fs::recursive_directory_iterator(driectory))
        {
            if (entry.is_regular_file())
            {
                fs::perms permissions = entry.status().permissions();
                if((permissions & fs::perms::owner_exec) != fs::perms::none && filename == entry.path().filename()){
                    return entry.path();
                }
            }
        }
    }
    return "";
}


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

