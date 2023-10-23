#include <iostream>
#include <vector>

#include "./headers/helper.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main() {
  Helper helper;

  helper.showReadMenu({"Login", "Sign Up"});
  system("pause");
  return 0;
}