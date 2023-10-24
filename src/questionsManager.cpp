#include "../headers/questionsManager.h"

#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "../headers/helper.h"
#include "../headers/question.h"
#include "../headers/user.h"

using std::map;
using std::max;
using std::pair;
using std::string;
using std::vector;

QuestionsManager::QuestionsManager() { this->lastID = 0; }

void QuestionsManager::loadDatabase() {
  Helper helper;

  this->lastID = 0;
  this->questionIDsThreadsMap.clear();
  this->questionObjectsMap.clear();

  vector<string> lines = helper.readFileLines("questions.txt");

  for (string& line : lines) {
    Question question(line);

    this->questionObjectsMap[question.questionID] = question;
    this->lastID = max(this->lastID, question.questionID);

    if (question.parentQuestionID != -1) {
      this->questionIDsThreadsMap[question.questionID].push_back(
          question.questionID);
    } else {
      this->questionIDsThreadsMap[question.parentQuestionID].push_back(
          question.questionID);
    }
  }
}

void QuestionsManager::fillUserQuestions(User& user) {
  user.questionIDsThreadMap.clear();
  user.questionIDsFromMe.clear();

  for (pair<int, vector<int>>& pair : this->questionIDsThreadsMap) {
    for (int& questionID : pair.second) {
      Question& question = this->questionObjectsMap[questionID];

      if (user.userID == question.fromUserID) {
        user.questionIDsFromMe.push_back(question.questionID);
      }

      if (user.userID == question.toUserID) {
        if (question.parentQuestionID != -1) {
          user.questionIDsThreadMap[question.questionID].push_back(
              question.questionID);
        } else {
          user.questionIDsThreadMap[question.parentQuestionID].push_back(
              question.questionID);
        }
      }
    }
  }
}

void QuestionsManager::printQuestionsToUser(User& user) {
  cout << "\n";

  if (user.questionIDsThreadMap.size() == 0) {
    cout << "No Questions.";
    return;
  }

  for (pair<int, vector<int>>& pair : user.questionIDsThreadMap) {
    for (int& questionID : pair.second) {
      Question& question = this->questionObjectsMap[questionID];

      question.printFromQuestion();
    }
  }
}

void QuestionsManager::printQuestionsFromUser(User& user) {
  cout << "\n";

  if (user.questionIDsFromMe.size() == 0) {
    cout << "No Questions.";
    return;
  }

  for (int& questionID : user.questionIDsFromMe) {
    Question question = this->questionObjectsMap[questionID];

    question.printToQuestion();
  }
}

int QuestionsManager::readQuestionID(User& user) {
  int questionID;

  cout << "Enter question id or -1 to cancel: ";
  cin >> questionID;

  if (questionID == -1) {
    return -1;
  }

  while (!this->questionObjectsMap.count(questionID)) {
    cout << "\nError: No question id such this entered id...Try again.\n\n";
    cout << "Enter question id or -1 to cancel: ";
    cin >> questionID;

    if (questionID == -1) {
      return -1;
    }
  }

  Question& question = this->questionObjectsMap[questionID];

  while (user.userID != question.toUserID) {
    cout << "\nError: No question id such this entered id...Try again.\n\n";
    cout << "Enter question id or -1 to cancel: ";
    cin >> questionID;

    if (questionID == -1) {
      return -1;
    }
  }

  return questionID;
}

int QuestionsManager::readQuestionIDThread(User& user) {
  int questionID;
  cout << "Enter Question id or -1 for new question: ";
  cin >> questionID;

  if (questionID == -1) {
    return -1;
  }

  while (!this->questionIDsThreadsMap.count(questionID)) {
    cout << "\nError: No question id such that...Try again\n";
    cout << "Enter Question id or -1 for new question: ";
    cin >> questionID;

    if (questionID == -1) {
      return -1;
    }
  }

  return questionID;
}

void QuestionsManager::answerQuestion(User& user) {
  int questionID = this->readQuestionID(user);

  if (questionID == -1) {
    return;
  }

  Question& question = this->questionObjectsMap[questionID];

  question.printFromQuestion();

  if (question.questionAnswer != "") {
    cout << "\nError: Answer already exists, Answer will updated\n\n";
  }

  cout << "Enter answer: ";
  getline(cin, question.questionAnswer);
  getline(cin, question.questionAnswer);
}

void QuestionsManager::deleteQuestion(User& user) {
  int questionID = this->readQuestionID(user);

  if (questionID == -1) {
    return;
  }

  vector<int> idsToRemove;

  if (this->questionIDsThreadsMap.count(questionID)) {
    idsToRemove = this->questionIDsThreadsMap[questionID];
    this->questionIDsThreadsMap.erase(questionID);
  } else {
    idsToRemove.push_back(questionID);

    for (pair<int, vector<int>>& pair : this->questionIDsThreadsMap) {
      vector<int>& questionIDsThread = pair.second;

      for (int i = 0; i < (int)questionIDsThread.size(); i++) {
        if (questionID == questionIDsThread[i]) {
          questionIDsThread.erase(questionIDsThread.begin() + i);
          break;
        }
      }
    }
  }

  for (int id : idsToRemove) {
    this->questionObjectsMap.erase(questionID);
  }
}

void QuestionsManager::askQuestion(User& user, pair<int, int> userInfo) {
  Question question;

  if (!userInfo.second) {
    cout << "Note this user not allow anonymous question\n";
    question.isAnonymousQuestion = 0;
  } else {
    cout << "Is anonymous question? (0 - 1): ";
    cin >> question.isAnonymousQuestion;
  }

  question.parentQuestionID = this->readQuestionIDThread(user);

  cout << "Enter question text: ";
  getline(cin, question.questionText);
  getline(cin, question.questionText);

  question.questionID = ++this->lastID;
  question.fromUserID = user.userID;
  question.toUserID = userInfo.first;

  this->questionObjectsMap[question.questionID] = question;

  if (question.parentQuestionID == -1) {
    this->questionIDsThreadsMap[question.questionID].push_back(
        question.questionID);
  } else {
    this->questionIDsThreadsMap[question.parentQuestionID].push_back(
        question.questionID);
  }
}

void QuestionsManager::listFeed() {
  for (pair<int, Question>& pair : this->questionObjectsMap) {
    Question& question = pair.second;

    if (question.questionAnswer == "") {
      continue;
    }

    question.printFeedQuestion();
  }
}

void QuestionsManager::updateDatabase() {
  Helper helper;
  vector<string> lines;

  for (pair<int, Question>& pair : this->questionObjectsMap) {
    lines.push_back(pair.second.toString());
  }

  helper.writeFileLines("questions.txt", lines, false);
}
