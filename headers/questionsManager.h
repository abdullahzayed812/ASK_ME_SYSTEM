#ifndef QUESTION_MANAGER_CLASS_H
#define QUESTION_MANAGER_CLASS_H 1

#include <map>
#include <vector>

// using std::map;
// using std::vector;

struct QuestionManager {
  map<int, vector<int>> questionIDQuestionThreadIDsMap;
  map<int, Question> questionIDQuestionObjectMap;
  int lastQuestionID;

  QuestionManager();
  void loadDatabase();
  void fillUserQuestions(User& user);
  void printUserToQuestions(User& user);
  void printUserFromQuestions(User& user);
  int readQuestionIDAny(User& user);
  int readQuestionIDThread(User& user);
  void answerQuestion(User& user);
  void deleteQuestion(User& user);
  void askQuestion(User& user, pair<int, int> toUserPair);
  void listFeed();
  void updateDatabase();
};

#endif