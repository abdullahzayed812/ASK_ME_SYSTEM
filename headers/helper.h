#ifndef HELPER_CLASS_H
#define HELPER_CLASS_H 1

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Helper {
  Helper();
  vector<string> readFileLines(string path);
  void writeFileLines(string path, vector<string> lines, bool append = true);
  vector<string> splitString(string line, string delimiter);
  int toNumber(string str);
  int readIntegerInRange(int low, int high);
  int showReadMenu(vector<string> choices);
};

#endif