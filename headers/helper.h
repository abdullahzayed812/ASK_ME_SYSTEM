#ifndef HELPER_CLASS_H
#define HELPER_CLASS_H 1

#include <string>
#include <vector>

// #include std::string;
// #include std::vector;

vector<string> readFileLines(string path);

void writeFileLines(string path, vector<string> lines, bool append);

vector<string> splitString(string line, string delimiter);

int toNumber(string str);

int readIntegerInRange(int low, int high);

int showReadMenu(vector<string> choices);

#endif