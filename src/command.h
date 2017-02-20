#ifndef COMMAND_H
#define COMMAND_H
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>




#include "base.h"

using namespace std;
using namespace boost;
class Command : public Base {
  
  private:
  Base *child; 
  string s;

  public:
  Command(){}
  Command(Base* child  ) {
    this->child = child;
  }
  ~Command(){}
  bool execute(); 
  string load(){return this->s;}
    
};

#endif