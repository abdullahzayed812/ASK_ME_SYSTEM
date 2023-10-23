#ifndef QUESTION_CLASS_H
#define QUESTION_CLASS_H 1

#include <string>

using std::string;

struct Question {
  int questionID;
  int parentQuestionID;
  int fromUserID;
  int toUserID;
  int isAnonymousQuestion;
  string questionText;
  string questionAnswer;

  Question();
  Question(string line);
  string toString();
  void printFromQuestion();
  void printToQuestion();
  void printFeedQuestion();
};

#endif