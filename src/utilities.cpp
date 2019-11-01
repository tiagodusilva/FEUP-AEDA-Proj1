#include "../include/utilities.h"

using namespace std;

namespace utl
{
    bool isNum(const string& s)
    {
        for (const char &i : s)
            if (i < '0' || i > '9')
                return false;
        return true;
    }

    void strLower(string & s)
    {
        for (char & i : s)
        {
            if (i >= 'A' && i <= 'Z')
                i += ('a' - 'A');
        }
    }

    void strUpper(string& s)
    {
        for (char & i : s)
        {
            if (i >= 'a' && i <= 'z')
                i += ('A' - 'a');
        }
    }

    void strTrim(string& s)
    {
        s.erase(0, s.find_first_not_of(' ')); // Trims spaces on the left
        s.erase(s.find_last_not_of(' '), string::npos); // Trims spaces on the right
    }

    bool isFileEmpty(ifstream & fin)
    {
        return fin.peek() == ifstream::traits_type::eof();
    }

    bool readConfirmation(char & c, string msg)
    {
        string s;
        do
        {
            cout << msg << " (y/n) ? ";
            getline(cin, s);
            if (cin.eof())
            {
                cin.clear();
                return false;
            }
        } while (s.size() != 1 || !(s.at(0) == 'y' || s.at(0) == 'Y' || s.at(0) == 'n' || s.at(0) == 'N'));

        strLower(s);
        c = s.at(0);
        return true;
    }

    void pauseConsole()
    {
        string trash;
        cout << "Press Enter to continue..." << endl;
        getline(cin, trash);
    }

    void clearConsole()
    {
        // Most portable way without using system(), conio.h, ncurses or an OS specific implementation
        // Saldy just moves everything up 40 lines...
        cout << string(40, '\n');
    }

    bool checkStream(std::istream & stream, std::string & error)
    {
        if (stream.eof())
        {
            error = "Reached end of file unexpectedly";
            return false;
        }
        if (stream.fail())
        {
            error = "Unexpected input";
            return false;
        }
        return true;
    }

    int getInt(istream &stream, int min, int max, string message){
        string res;
        int res_num;
        bool valid=false;

        do{
	    cout << message << endl;
            getline(stream, res);
            clearConsole();
            if(isNum(res) && res != "") {
                res_num = stoi(res);
                if (res_num >= min && res_num <= max)
                    valid = true;
            }
        } while(!valid);

        return res_num;
    }

}
