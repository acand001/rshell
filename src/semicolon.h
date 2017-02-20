#ifndef SEMICOLON_H
#define SEMICOLON_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "base.h"
#include "command.h"
using namespace std;

class Semicolon : public Base{
       
    private: 
    Base* single;
    string str;
    
   public:
   Semicolon(){}
    Semicolon(Base* o){
        single = o;
    }
  
    ~Semicolon(){}
    
    bool execute();
    string load();
      

};
#endif