#include <filesystem>
#include<iostream>

#include<string>
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

string getCurrnetWorkingDirectory(){
    return fs::current_path();
}

int cdToAbsolutePath(string absPath){
    if(!fs::is_directory(absPath)){
        return 0;
    }
    
    fs::current_path(absPath);
    return 1;
}