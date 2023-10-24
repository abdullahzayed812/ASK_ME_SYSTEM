#include "../headers/usersManager.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "../headers/helper.h"
#include "../headers/user.h"

using std::cin;
using std::cout;
using std::map;
using std::max;
using std::pair;
using std::string;
using std::vector;

UsersManager::UsersManager() { this->lastID = 0; }

void UsersManager::loadDatabase() {
  this->lastID = 0;
  this->userObjectsMap.clear();

  Helper helper;

  vector<string> lines = helper.readFileLines("users.txt");

  for (const string& line : lines) {
    User user(line);

    this->userObjectsMap[user.username] = user;
    this->lastID = max(lastID, user.userID);
  }
}

void UsersManager::updateDatabase(User& user) {
  string line = user.toString();
  vector<string> lines(1, line);

  Helper helper;
  helper.writeFileLines("users.txt", lines);
}

void UsersManager::login() {
  this->loadDatabase();

  while (true) {
    cout << "Enter username and password: ";
    cin >> this->currentUser.username >> this->currentUser.password;

    if (!this->userObjectsMap.count(this->currentUser.username)) {
      cout << "\nError: Invalid username or password...Try again.\n\n";
      continue;
    }

    User userExist = this->userObjectsMap[this->currentUser.username];

    if (this->currentUser.password != userExist.password) {
      cout << "\nError: Invalid username or password...Try again.\n\n";
      continue;
    }

    this->currentUser = userExist;
    break;
  }
}

void UsersManager::signUp() {
  while (true) {
    cout << "Enter user name. (NO Spaces): ";
    cin >> this->currentUser.username;

    if (this->userObjectsMap.count(this->currentUser.username)) {
      cout << "Already used, Try again.\n\n";
    } else {
      break;
    }
  }

  cout << "Enter password: ";
  cin >> this->currentUser.password;

  cout << "Enter name: ";
  cin >> this->currentUser.name;

  cout << "Enter email: ";
  cin >> this->currentUser.email;

  cout << "Allow anonymous question or not (0 - 1): ";
  cin >> this->currentUser.allowAnonymousQuestions;

  this->currentUser.userID = ++this->lastID;
  this->userObjectsMap[currentUser.username] = currentUser;

  this->updateDatabase(currentUser);
}

void UsersManager::accessSystem() {
  Helper helper;
  int choice = helper.showReadMenu({"Login", "Sign Up"});

  if (choice == 1) {
    this->login();
  } else {
    this->signUp();
  }
}

void UsersManager::listSystemUsers() {
  for (const pair<string, User>& pair : this->userObjectsMap) {
    cout << "User id " << pair.second.userID << "\tName: " << pair.second.name
         << "\n";
  }
}

pair<int, int> UsersManager::readUserInfo() {
  int userID;

  cout << "Enter user id or -1 to cancel: ";
  cin >> userID;

  if (userID == -1) {
    pair<int, int> p(-1, -1);
    return p;
  }

  for (const pair<string, User>& userPair : this->userObjectsMap) {
    if (userPair.second.userID == userID) {
      pair<int, int> p(userID, userPair.second.allowAnonymousQuestions);
      return p;
    }
  }

  cout << "Invalid user id. Try again\n\n";
  return this->readUserInfo();
}