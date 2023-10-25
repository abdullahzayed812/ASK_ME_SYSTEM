#ifndef ASK_SYSTEM_CLASS_H
#define ASK_SYSTEM_CLASS_H 1

#include "./questionsManager.h"
#include "./usersManager.h"

// g++ .\main.cpp .\src\askSystem.cpp .\src\helper.cpp .\src\question.cpp
// .\src\questionsManager.cpp .\src\user.cpp .\src\usersManager.cpp -o main

struct AskSystem {
  UsersManager usersManager;
  QuestionsManager questionsManager;

  void loadDatabase(bool fillCurrentUserData = false);
  void run();
};

#endif