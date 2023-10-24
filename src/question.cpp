#include "../headers/question.h"

#include <assert.h>

#include <iostream>
#include <sstream>
#include <string>

#include "../headers/helper.h"

using std::cout;
using std::ostringstream;
using std::string;

Question::Question() {
  this->questionID = this->parentQuestionID = this->fromUserID =
      this->toUserID = -1;
  this->isAnonymousQuestion = 1;
}

Question::Question(string line) {
  Helper helper;
  vector<string> questionInfo = helper.splitString(line);
  assert(questionInfo.size() == 7);

  this->questionID = helper.toNumber(questionInfo[0]);
  this->parentQuestionID = helper.toNumber(questionInfo[1]);
  this->fromUserID = helper.toNumber(questionInfo[2]);
  this->toUserID = helper.toNumber(questionInfo[3]);
  this->isAnonymousQuestion = helper.toNumber(questionInfo[4]);
  this->questionText = helper.toNumber(questionInfo[5]);
  this->questionAnswer = helper.toNumber(questionInfo[6]);
}

string Question::toString() {
  ostringstream oss;
  oss << this->questionID << "," << this->parentQuestionID << ","
      << this->fromUserID << "," << this->toUserID << ","
      << this->isAnonymousQuestion << "," << this->questionText << ","
      << this->questionAnswer;

  return oss.str();
}

void Question::printFromQuestion() {
  string prefix;

  if (this->parentQuestionID != -1) {
    prefix = "\tThread: ";
  }

  cout << prefix << "Question id (" << this->questionID << ")";

  if (!this->isAnonymousQuestion) {
    cout << " from user id (" << this->fromUserID << ")";
  }

  cout << "\n";
  cout << "\t\tQuestion: " << this->questionText;
  cout << "\n";

  if (this->questionAnswer != "") {
    cout << "\t\tAnswer: " << this->questionAnswer << "\n";
  }

  cout << "\n";
}

void Question::printToQuestion() {
  cout << "Question id (" << this->questionID << ")";

  if (!this->isAnonymousQuestion) {
    cout << " !AQ";
  }

  cout << " to user id (" << this->toUserID << ")";
  cout << "\n";
  cout << "\t\tQuestion: " << this->questionText;
  cout << "\n";

  if (this->questionAnswer != "") {
    cout << "\t\tAnswer: " << this->questionAnswer << "\n";
  } else {
    cout << "\tNot answered yet!"
         << "\n";
  }
}

void Question::printFeedQuestion() {
  if (this->parentQuestionID != -1) {
    cout << "Thread parent question id (" << this->parentQuestionID << ")";
  }

  cout << "\tQuestion id (" << this->questionID << ")";

  if (!this->isAnonymousQuestion) {
    cout << " from user id (" << this->fromUserID << ")";
  }

  cout << " to user id (" << this->toUserID << ")";
  cout << "\n";
  cout << "\ttQuestion: " << this->questionText;
  cout << "\n";

  if (this->questionAnswer != "") {
    cout << "\t\tAnswer: " << this->questionAnswer;
  }
}