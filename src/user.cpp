#include "../headers/user.h"

#include <assert.h>

#include <iostream>
#include <sstream>
#include <string>

#include "../headers/helper.h"

using std::cout;
using std::ostringstream;
using std::string;

User::User() { this->userID = this->allowAnonymousQuestions = -1; }

User::User(string line) {
  Helper helper;
  vector<string> userInfo = helper.splitString(line);
  assert(userInfo.size() == 6);

  this->userID = helper.toNumber(userInfo[0]);
  this->username = userInfo[1];
  this->password = userInfo[2];
  this->name = userInfo[3];
  this->email = userInfo[4];
  this->allowAnonymousQuestions = helper.toNumber(userInfo[5]);
}

string User::toString() {
  ostringstream oss;
  oss << this->userID << "," << this->username << "," << this->password << ","
      << this->name << "," << this->email << this->allowAnonymousQuestions;

  return oss.str();
}

void User::print() {
  cout << "User " << this->userID << ", " << this->password << ", "
       << this->name << ", " << this->email << "\n";
}