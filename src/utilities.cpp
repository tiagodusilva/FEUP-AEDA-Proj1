#include <cmath>

#include "../include/utilities.h"

using namespace std;

namespace utl {

bool
isNum(const string& s)
{
  for (const char& i : s)
    if (i < '0' || i > '9')
      return false;
  return true;
}

void
strLower(string& s)
{
  for (char& i : s) {
    if (i >= 'A' && i <= 'Z')
      i += ('a' - 'A');
  }
}

void
strUpper(string& s)
{
  for (char& i : s) {
    if (i >= 'a' && i <= 'z')
      i += ('A' - 'a');
  }
}

string&
ltrim(std::string& str, const std::string& chars)
{
  str.erase(0, str.find_first_not_of(chars));
  return str;
}

string&
rtrim(std::string& str, const std::string& chars)
{
  str.erase(str.find_last_not_of(chars) + 1);
  return str;
}

string&
trim(std::string& str, const std::string& chars)
{
  return ltrim(rtrim(str, chars), chars);
}

bool
isStrEmpty(std::string str)
{
  return (trim(str) == "");
}

bool
isFileEmpty(ifstream& fin)
{
  return fin.peek() == ifstream::traits_type::eof();
}

bool
readConfirmation(char& c, const std::string& msg)
{
  string s;
  do {
    cout << msg << " (y/n) ? ";
    getline(cin, s);
    if (cin.eof()) {
      cin.clear();
      return false;
    }
  } while (s.size() != 1 || !(s.at(0) == 'y' || s.at(0) == 'Y' ||
                              s.at(0) == 'n' || s.at(0) == 'N'));

  strLower(s);
  c = s.at(0);
  return true;
}

void
pauseConsole()
{
  string trash;
  cout << "Press Enter to continue..." << endl;
  getline(cin, trash);
}

void
clearConsole()
{
  // Most portable way without using system(), conio.h, ncurses or an OS
  // specific implementation
  cout << string(CLEAR_CONSOLE_NEW_LINES, '\n');
}

bool
checkStream(std::istream& stream, string& error)
{
  if (stream.eof()) {
    error = "Reached end of file unexpectedly";
    return false;
  }

  if (stream.fail()) {
    error = "Unexpected input";
    return false;
  }

  return true;
}

int
getInt(istream& stream, int min, int max, const string& message)
{
  int res_num;
  bool valid = false;

  do {
    cout << message << endl;
    stream >> res_num;
    clearConsole();
    if (stream.fail()) {
      stream.clear();
      ignore(stream);
    }
    else if ((stream.peek() == ' ' || stream.peek() == '\n' || stream.eof()) &&
             res_num >= min && res_num <= max)
      valid = true;

  } while (!valid);
  ignore(stream); // remove \n when reading an int

  return res_num;
}

float
getDistance(std::tuple<float, float> point1, std::tuple<float, float> point2)
{
	return sqrt(pow(get<0>(point1) - get<0>(point2), 2) + pow(get<1>(point1) - get<1>(point2), 2));
}

bool
file_exists(const std::string& name)
{
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}

float
coord_dist(const std::tuple<float, float>& c1,
           const std::tuple<float, float>& c2)
{
  return sqrt(pow(get<0>(c2) - get<0>(c1), 2) + pow(get<1>(c2) - get<1>(c1), 2));
}

} // namespace utl
