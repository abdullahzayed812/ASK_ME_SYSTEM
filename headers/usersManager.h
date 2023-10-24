#ifndef USERS_MANAGER_CLASS_H
#define USERS_MANAGER_CLASS_H 1

#include <map>
#include <string>
#include <utility>

#include "./user.h"

using std::map;
using std::pair;
using std::string;

struct UsersManager {
  map<string, User> userObjectsMap;
  User currentUser;
  int lastID;

  UsersManager();
  void loadDatabase();
  void updateDatabase(User& user);
  void login();
  void signUp();
  void accessSystem();
  void listSystemUsers();
  pair<int, int> readUserInfo();
};

#endif