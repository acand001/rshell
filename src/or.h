#ifndef OR_H
#define OR_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "base.h"
#include "command.h"

using namespace std;

class Or : public Base{
 
 private:
   Base* left; 
   Base* right;  
   string s;
   
 public:
  Or(){}
   Or(Base*l, Base*r)  {
       left = l;
       right = r;
   }

   ~Or(){}
      bool execute();

   string load();
     
};

#endif