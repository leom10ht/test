//Using C++17

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

using std::vector;
using std::string;
using std::ifstream;
class Solution {
public:
    void SearchWordsInFile(vector<string>& vec, const string& search, const string& path)
    {
        string x;
        try {
            for (auto& s : vec) {
                ifstream file_text(path + '/' + s);
                if (file_text.is_open())
                {
                    while (getline(file_text, x))
                    {
                        if (x.find(search, 0) != string::npos) {
                            std::cout << "#################" << '\n';
                            std::cout << "Found in: " << s << '\n';
                        }
                    }
                    file_text.close();
                }

                else std::cout << "Unable to open file: " << s << '\n';
            }
        }
        catch (const std::ios_base::failure& fail) {
            std::cout << fail.what() << '\n';
        }
    }
    vector<string> FindFolder(const string& path)
    {
        vector<string> vec;
        try {
            for (const auto& entry : std::filesystem::directory_iterator(path))
            {
                const string s1 = entry.path().generic_string();
                const auto pos = s1.find_last_of('/');
                vec.push_back(s1.substr(pos + 1));
            }
        }
        catch (std::filesystem::filesystem_error const& ex)
        {
            std::cout << ex.code().message() << '\n';
        }
        return vec;
    }
    void ShowFolder(const vector<string>& vec)
    {
        std::cout << "List Files\n";
        for (const auto& iter : vec)
            std::cout << iter << '\n';
    }
};

int main(int argc, char const* argv[])
{
    /**/
    Solution test;
    if (argc == 2)
    {
        vector<string>res = test.FindFolder(std::filesystem::current_path().generic_string());
        //test.ShowFolder(res);
        test.SearchWordsInFile(res, argv[1], std::filesystem::current_path().generic_string());
    }
    else if (argc == 3)
    {
        vector<string>res = test.FindFolder(argv[2]);
       //test.ShowFolder(res);
        test.SearchWordsInFile(res, argv[1], argv[2]);
    }
    else
        std::cout << "Enter: <words need search> <the path>";
    return 0;
}