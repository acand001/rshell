#include "and.h"
using namespace std;


And::And() {}
And::And(Base*left, Base* right) {
        this->left = left;
        this->right = right;
    }
  
bool And::execute() {
    
  Command* command = new Command(left);
      if(command->execute()) {
        //cout << " left side of && executed, now executing right "<< endl;
          Command* command2 = new Command(right); 
              command2->execute();
      }
      else {
          return false;
      }
    return false;
}

string And::load() {
  return s;
}