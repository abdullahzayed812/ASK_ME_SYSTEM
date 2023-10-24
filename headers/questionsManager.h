#ifndef QUESTION_MANAGER_CLASS_H
#define QUESTION_MANAGER_CLASS_H 1

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "./question.h"
#include "./user.h"

using std::map;
using std::pair;
using std::string;
using std::vector;

struct QuestionsManager {
  map<int, vector<int>> questionIDsThreadsMap;
  map<int, Question> questionObjectsMap;
  int lastID;

  QuestionsManager();
  void loadDatabase();
  void fillUserQuestions(User& user);
  void printQuestionsToUser(User& user);
  void printQuestionsFromUser(User& user);
  int readQuestionID(User& user);
  int readQuestionIDThread(User& user);
  void answerQuestion(User& user);
  void deleteQuestion(User& user);
  void askQuestion(User& user, pair<int, int> toUserPair);
  void listFeed();
  void updateDatabase();
};

#endif