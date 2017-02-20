#ifndef AND_H
#define AND_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "base.h"
#include "command.h"

using namespace std;

class And : public Base{
 
  private:
  Base* right;
  Base* left;
  string s;

  public:
  And();
  And(Base*left, Base*right);
  // And(Base*left, Base* right) {
  //       this->left = left;
  //       this->right = right;
  //   }
  
    ~And(){}
    
  //BOOL FUNCTION HERE
  bool execute ();
  string load();

};
#endif