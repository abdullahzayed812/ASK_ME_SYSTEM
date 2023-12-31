#ifndef USER_CLASS_H
#define USER_CLASS_H 1

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

struct User {
  int userID;
  string username;
  string password;
  string name;
  string email;
  int allowAnonymousQuestions;
  vector<int> questionIDsFromMe;
  map<int, vector<int>> questionIDsThreadMap;

  User();
  User(string line);
  string toString();
  void print();
};

#endif