#include "../headers/helper.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::fstream;
using std::string;
using std::vector;

vector<string> readFileLines(string path) {
  vector<string> lines;
  fstream fileHandler(path.c_str());

  if (fileHandler.fail()) {
    cout << "\n\nERROR: Can't open the file\n\n";
    return lines;
  }

  string line;
  while (getline(fileHandler, line)) {
    if (line.size() == 0) {
      continue;
    }
    lines.push_back(line);
  }

  fileHandler.close();

  return lines;
}

void writeFileLines(string path, vector<string> lines, bool append = true) {
  auto status = ios::in | ios::out | ios::append;

  if (!append) {
    status = ios::in | ios::out | ios::trunc;
  }

  fstream fileHandler(path.c_str(), status);

  if (fileHandler.fail()) {
    cout << "\n\nERROR: Can't open the file\n\n";
  }

  for (string line : lines) {
    fileHandler << line << "\n";
  }
}

vector<string> splitString(string line, string delimiter = ",") {
  vector<string> strs;
  int pos;
  string substring;

  while ((pos = line.find(delimiter)) != -1) {
    substring = line.substr(0, pos);
    str.push_back(substring);
    line.erase(0, pos + delimiter.length());
  }

  strs.push_back(line);
  return strs;
}

int toNumber(string str) {
  istringstream iss(str);

  int num;
  iss >> num;

  return num;
}

int readIntegerInRange(int low, int high) {
  int result;

  if ((result >= low) && (result <= high)) {
    return result;
  }

  cout << "ERROR: invalid number...Try again\n";
  return readIntegerInRange(low, high);
}

int showReadMenu(vector<string> choices) {
  cout << "\nMenu\n";

  for (int i = 0; i < (int)choices.size(); i++) {
    cout << "\t" << i + 1 << ": " << choices[i] << "\n";
  }

  return readIntegerInRange(1, choices.size());
}
