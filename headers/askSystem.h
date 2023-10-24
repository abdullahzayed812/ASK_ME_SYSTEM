#ifndef ASK_SYSTEM_CLASS_H
#define ASK_SYSTEM_CLASS_H 1

#include "./questionsManager.h"
#include "./usersManager.h"

struct AskSystem {
  UsersManager usersManager;
  QuestionsManager questionsManager;

  void loadDatabase(bool fillCurrentUserData = false);
  void run();
};

#endif