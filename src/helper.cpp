#include "../headers/helper.h"

#include <assert.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::fstream;
using std::ios;
using std::istringstream;
using std::string;
using std::vector;

Helper::Helper(){};

vector<string> Helper::readFileLines(string path) {
  vector<string> result;

  fstream fileHandler(path.c_str());

  if (fileHandler.fail()) {
    cout << "\n\nError: Can't read this file\n\n";
    return result;
  }

  string line;

  while (getline(fileHandler, line)) {
    if (line.length() == 0) {
      continue;
    }

    result.push_back(line);
  }

  fileHandler.close();
  return result;
}

void Helper::writeFileLines(string path, vector<string> lines, bool append) {
  auto status = ios::in | ios::out | ios::app;

  if (!append) {
    status = ios::in | ios::out | ios::trunc;
  }

  fstream fileHandler(path.c_str(), status);

  if (fileHandler.fail()) {
    cout << "\n\n:Error: Can't read this file\n\n";
    return;
  }

  for (const string& line : lines) {
    fileHandler << line << "\n";
  }

  fileHandler.close();
}

vector<string> Helper::splitString(string str, string delimiter) {
  vector<string> result;

  string subString;
  int pos = (int)str.find(delimiter);

  while (pos != -1) {
    subString = str.substr(0, pos);
    result.push_back(subString);
    str.erase(0, pos + delimiter.length());
    pos = (int)str.find(delimiter);
  }

  result.push_back(str);
  return result;
}

int Helper::toNumber(string str) {
  istringstream iss(str);
  int num;
  iss >> num;

  return num;
}

int Helper::readIntegerInRange(int low, int high) {
  int value;

  cout << "\nEnter number in range " << low << " - " << high << ": ";
  cin >> value;

  while ((value < low || value > high)) {
    cout << "Error: invalid number...Try again\n";
    cin >> value;
  }

  return value;
}

int Helper::showReadMenu(vector<string> choices) {
  cout << "\n\nMenu:\n";

  for (int i = 0; i < (int)choices.size(); i++) {
    cout << "\t" << i + 1 << ": " << choices[i] << "\n";
  }

  return readIntegerInRange(1, choices.size());
}