#include <iostream>
#include <vector>

using std::cout;
using std::string;
using std::vector;

vector<string> splitString(string line, string delimiter = ",") {
  vector<string> strs;
  int pos;
  string substring;

  while ((pos = line.find(delimiter)) != -1) {
    substring = line.substr(0, pos);
    strs.push_back(substring);
    line.erase(0, pos + delimiter.length());
  }

  strs.push_back(line);
  return strs;
}

int main() {
  vector<string> res = splitString("101,mohamed,software engineer,10");

  for (auto line : res) {
    cout << line << "\n";
  }

  return 0;
}