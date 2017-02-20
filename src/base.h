#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <cstdlib>

using namespace std;

class Base {
    
    public:

    /* Constructors */
    Base(){};
      virtual ~Base()  {
        
    };
    /* Pure Virtual Functions */
    virtual bool execute () = 0;
    virtual string load() = 0;

    
};
#endif