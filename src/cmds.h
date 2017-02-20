#ifndef CMDS_H
#define CMDS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "base.h"

using namespace std;

class Cmds : public Base {
 
 private:
    string cmds;
 
 public:
    //Constructor
    Cmds(string str){

        cmds = str;
    }
     
     bool execute() {return true;}
     
     string load(){
      return cmds;
     }
     ~Cmds(){}
  
};

#endif