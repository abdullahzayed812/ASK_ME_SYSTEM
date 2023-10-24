#include "../headers/askSystem.h"

#include "../headers/helper.h"
#include "../headers/questionsManager.h"
#include "../headers/user.h"
#include "../headers/usersManager.h"

void AskSystem::loadDatabase(bool fillCurrentUserData) {
  this->usersManager.loadDatabase();
  this->questionsManager.loadDatabase();

  if (fillCurrentUserData) {
    this->questionsManager.fillUserQuestions(this->usersManager.currentUser);
  }
}

void AskSystem::run() {
  this->loadDatabase();
  this->usersManager.accessSystem();
  this->questionsManager.fillUserQuestions(this->usersManager.currentUser);

  vector<string> menu;
  menu.push_back("Print Questions To Me");
  menu.push_back("Print Questions From Me");
  menu.push_back("Answer Question");
  menu.push_back("Delete Question");
  menu.push_back("Ask Question");
  menu.push_back("List System Users");
  menu.push_back("Feed");
  menu.push_back("Logout");

  while (true) {
    Helper helper;
    int choice = helper.showReadMenu(menu);

    this->loadDatabase(true);

    switch (choice) {
      case 1: {
        this->questionsManager.printQuestionsToUser(
            this->usersManager.currentUser);
        break;
      }
      case 2: {
        this->questionsManager.printQuestionsFromUser(
            this->usersManager.currentUser);
        break;
      }
      case 3: {
        this->questionsManager.answerQuestion(this->usersManager.currentUser);
        this->questionsManager.updateDatabase();
        break;
      }
      case 4: {
        this->questionsManager.deleteQuestion(this->usersManager.currentUser);
        this->questionsManager.fillUserQuestions(
            this->usersManager.currentUser);
        this->questionsManager.updateDatabase();
        break;
      }
      case 5: {
        pair<int, int> userData = this->usersManager.readUserInfo();

        if (userData.first != -1) {
          this->questionsManager.askQuestion(this->usersManager.currentUser,
                                             userData);
          this->questionsManager.updateDatabase();
        }
        break;
      }
      case 6: {
        this->usersManager.listSystemUsers();
        break;
      }
      case 7: {
        this->questionsManager.listFeed();
        break;
      }
      default:
        break;
    }
  }
}