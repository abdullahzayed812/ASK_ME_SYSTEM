#include "../headers/askSystem.h"

#include <iostream>

#include "../headers/helper.h"
#include "../headers/questionsManager.h"
#include "../headers/user.h"
#include "../headers/usersManager.h"
using std::cout;

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

    // System crash here, will fix it near.
    cout << "Before load database second time.\n";
    this->loadDatabase(true);
    cout << "After load database second time.";

    if (choice == 1) {
      this->questionsManager.printQuestionsToUser(
          this->usersManager.currentUser);
    } else if (choice == 2) {
      this->questionsManager.printQuestionsFromUser(
          this->usersManager.currentUser);
    } else if (choice == 3) {
      this->questionsManager.answerQuestion(this->usersManager.currentUser);
      this->questionsManager.updateDatabase();
    } else if (choice == 4) {
      this->questionsManager.deleteQuestion(this->usersManager.currentUser);
      this->questionsManager.fillUserQuestions(this->usersManager.currentUser);
      this->questionsManager.updateDatabase();
    } else if (choice == 5) {
      pair<int, int> userData = this->usersManager.readUserInfo();

      if (userData.first != -1) {
        this->questionsManager.askQuestion(this->usersManager.currentUser,
                                           userData);
        this->questionsManager.updateDatabase();
      }
    } else if (choice == 6) {
      this->usersManager.listSystemUsers();
    } else if (choice == 7) {
      this->questionsManager.listFeed();
    } else {
      break;
    }
    // cout << "Reached here.";
    // switch (choice) {
    //   case 1: {
    //     cout << "Reached here";
    //     this->questionsManager.printQuestionsToUser(
    //         this->usersManager.currentUser);
    //     break;
    //   }
    //   case 2: {
    //     this->questionsManager.printQuestionsFromUser(
    //         this->usersManager.currentUser);
    //     break;
    //   }
    //   case 3: {
    //     this->questionsManager.answerQuestion(this->usersManager.currentUser);
    //     this->questionsManager.updateDatabase();
    //     break;
    //   }
    //   case 4: {
    //     this->questionsManager.deleteQuestion(this->usersManager.currentUser);
    //     this->questionsManager.fillUserQuestions(
    //         this->usersManager.currentUser);
    //     this->questionsManager.updateDatabase();
    //     break;
    //   }
    //   case 5: {
    //     pair<int, int> userData = this->usersManager.readUserInfo();

    //     if (userData.first != -1) {
    //       this->questionsManager.askQuestion(this->usersManager.currentUser,
    //                                          userData);
    //       this->questionsManager.updateDatabase();
    //     }
    //     break;
    //   }
    //   case 6: {
    //     this->usersManager.listSystemUsers();
    //     break;
    //   }
    //   case 7: {
    //     this->questionsManager.listFeed();
    //     break;
    //   }
    //   default:
    //     break;
    // }
  }
  // run();
}